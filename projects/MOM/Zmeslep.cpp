#ifdef HAVE_CONFIG_H
 #include <config.hpp>
#endif

#ifdef USE_OMP
 #include <omp.h>
#endif

#define EXTERN_MESLEP
 #include <Zmeslep.hpp>

#include <ingredients.hpp>
#include <oper.hpp>

#include <prop.hpp>

vector<dcompl_t> build_mesloop(const vector<mom_conf_lprops_t> &props_lep)
{
  //! projected lepton propagator with insertion
  vector<dcompl_t> mesloop(iGl_ipGl_iclust_ind.max());
  
  // NB: the lepton loop is fully amputated
#pragma omp parallel for
  for(size_t i=0;i<iGl_ipGl_iclust_ind.max();i++)
    {
      vector<size_t> comps=iGl_ipGl_iclust_ind(i);
      const size_t iGl=comps[0],ipGl=comps[1],iclust=comps[2];
      const mom_conf_lprops_t &pl=props_lep[iclust];
      
      mesloop[i]=(pl.F*lepGamma[iGl]*(lepGamma[0]-lepGamma[5])*lepGamma[ipGl].adjoint()).trace()/4.0; //normalization for the single gamma
    }
  
  return mesloop;
}

void build_jackknifed_meslep_vert_Gamma(jqprop_t &jvert,const qprop_t &prop1,const size_t iGl,const qprop_t &prop2,const vector<dcompl_t> &lloop,size_t ipGl,size_t iclust)
{
  const size_t iGq=iGl;
  
  const size_t imesloop=iGl_ipGl_iclust_ind({iGl,ipGl,iclust});
  const qprop_t contr=prop1*quaGamma[iGq]*quaGamma[5]*prop2.adjoint()*quaGamma[5]*lloop[imesloop];
  jvert[iclust]+=contr;
  
  cout<<"iGl: "<<iGl<<
    ", ipGl: "<<ipGl<<
    ", iclust: "<<iclust<<
    ", mesloop: "<<lloop[imesloop]<<
    ", prop1: "<<prop1(0,0)<<
    ", prop2: "<<prop2(0,0)<<
    ", res: "<<contr(0,0)<<
    endl;
}

void build_all_mr_gmeslep_jackkniffed_verts(jmeslep_vert_t &j,const vector<m_r_mom_conf_qprops_t> &props1,const vector<m_r_mom_conf_qprops_t> &props2,
					    const vector<mom_conf_lprops_t> &props_lep,const index_t &im_r_ind)
{
  const size_t nm=im_r_ind.max(0);
  const size_t nr=im_r_ind.max(1);
  
  vector<dcompl_t> mesloop=build_mesloop(props_lep);
  
  //! help finding the meslep/clust combo
  index_t im_r_iclust_ind=im_r_ind*index_t({{"clust",njacks}});
  index_t im_r_im_r_iGl_ipGl_iclust_ind=im_r_ind*im_r_ind*iGl_ipGl_iclust_ind;
  index_t im_r_im_r_iGl_ipGl_ind=im_r_ind*im_r_ind*index_t({{"Gl",nGamma},{"pGl",nGamma}});
  index_t im_r_im_r_iop_ipGl_ind({{"m_fw",nm},{"r_fw",nr},{"m_bw",nm},{"r_bw",nr},{"zBil",nZbil},{"pGl",nGamma}});
  
#pragma omp parallel for
   for(size_t i=0;i<im_r_im_r_iGl_ipGl_iclust_ind.max();i++)
     {
       //decript bilinar/jack
       vector<size_t> comps=im_r_im_r_iGl_ipGl_iclust_ind(i);
       
       //decript props to combine and which Gamma to create
       const size_t im_fw=comps[0],r_fw=comps[1];
       const size_t im_bw=comps[2],r_bw=comps[3];
       const size_t iGl=comps[4],ipGl=comps[5];
       const size_t iclust=comps[6];
       
       //proxy for vector and props
       const m_r_mom_conf_qprops_t &p1=props1[im_r_iclust_ind({im_fw,r_fw,iclust})];
       const m_r_mom_conf_qprops_t &p2=props2[im_r_iclust_ind({im_bw,r_bw,iclust})];
       
       //create list of operations
       vector<tuple<vector<jqprop_t>*,const qprop_t*,const qprop_t*>> list=
	 {{&j.ML1,&p1.F,&p2.LO},
	  {&j.ML2,&p1.LO,&p2.F}};
       
       //create the vertex
       const size_t im_r_im_r_iGl_ipGl=im_r_im_r_iGl_ipGl_ind({im_fw,r_fw,im_bw,r_bw,iGl,ipGl});
       for(auto &o : list)
	 build_jackknifed_meslep_vert_Gamma((*get<0>(o))[im_r_im_r_iGl_ipGl],
					    *get<1>(o),
					    iGl,
					    *get<2>(o),
					    mesloop,
					    ipGl,
					    iclust);
     }
}

djvec_t compute_proj_measlep(const vjqprop_t &jprop_inv1,const vector<jqprop_t> &jverts,const vjqprop_t &jprop_inv2,const index_t &im_r_ind)
{
  using namespace meslep;
  
  const index_t im_r_im_r_iop_iproj_ind=im_r_ind*im_r_ind*index_t({{"iop",nZbil},{"iproj",nZbil}});
  const index_t im_r_im_r_iop_ipGl_ind=im_r_ind*im_r_ind*index_t({{"iop",nZbil},{"pGammaL",nGamma}});
  const index_t im_r_im_r_iGl_ipGl_ind=im_r_ind*im_r_ind*index_t({{"iGamma",nGamma},{"pGammaL",nGamma}});
  const index_t ind({{"rest",im_r_im_r_iop_iproj_ind.max()},{"ijack",njacks+1}});
  
  //Each operator on the quark side needs to incorporate the structure G(1+-g5)
  // whereas jverts incorporates only G
  //We decompose it in the 1 and g5 parts, putting the sign explicitly
  //const vector<vector<size_t>> &ipGl_of_iproj=iGq_of_iop; // here instead 1-g5 was already included at lepton projection
  djvec_t pr(im_r_im_r_iop_iproj_ind.max());
  
  using namespace meslep;

  //Decompose the 1+-g5 on the Clifford basis
  vector<vector<vector<pair<size_t,dcompl_t>>>> reco_pQ(nZbil);
  for(size_t iop=0;iop<nZbil;iop++)
    {
      reco_pQ[iop].resize(iGq_of_iop[iop].size());
      const int g5_sign=g5_sign_of_iop[iop];
      
      for(size_t i=0;i<iGq_of_iop[iop].size();i++)
	{
	  const size_t iGq=iGq_of_iop[iop][i];
	  vector<dcompl_t> d=Clifford_decompose(quaGamma,quaGamma[iGq]*(quaGamma[0]+g5_sign*quaGamma[5]));
	  for(size_t b=0;b<16;b++)
	    if(d[b]!=0.0)
	      reco_pQ[iop][i].push_back(make_pair(b,d[b]));
	}
    }
    
#pragma omp parallel for
  for(size_t i=0;i<ind.max();i++)
    {
      //split im_r_im_r_iop_iproj and ijack
      vector<size_t> comps=ind(i);
      const size_t im_r_im_r_iop_iproj=comps[0],ijack=comps[1];
      const vector<size_t> im_r_im_r_iop_iproj_comps=im_r_im_r_iop_iproj_ind(im_r_im_r_iop_iproj);
      
      //get im and r for fw and back, and iop and iproj
      const size_t im_fw=im_r_im_r_iop_iproj_comps[0],r_fw=im_r_im_r_iop_iproj_comps[1];
      const size_t im_bw=im_r_im_r_iop_iproj_comps[2],r_bw=im_r_im_r_iop_iproj_comps[3];
      const size_t iop=im_r_im_r_iop_iproj_comps[4],iproj=im_r_im_r_iop_iproj_comps[5];
      
      const double norm=12.0*sqr(iGq_of_iop[iop].size())*2.0; //2 comes form 1-g5 normalziation
      
      const size_t ip1=im_r_ind({im_fw,r_fw});
      const size_t ip2=im_r_ind({im_bw,r_bw});
      const qprop_t &prop_inv1=jprop_inv1[ip1][ijack];
      const qprop_t &prop_inv2=jprop_inv2[ip2][ijack];
      
      //loop on all operators
      double &out=pr[im_r_im_r_iop_iproj][ijack];
      out=0.0;
      
      for(size_t i=0;i<iGq_of_iop[iop].size();i++)
	for(auto &contr : reco_pQ[iop][i])
	  {
	    const size_t iGq=contr.first;
	    const dcompl_t coeff=contr.second;
	    
	    for(auto &ipGl : ipGl_of_iproj[iproj])
	      {
		const size_t ipGq=ipGl; //Projecting on quark side with the same gamma (will insert the 1+-g5)
		const size_t im_r_im_r_iGl_ipGl=im_r_im_r_iGl_ipGl_ind({im_fw,r_fw,im_bw,r_bw,iGq,ipGl});
		const qprop_t &vert=jverts[im_r_im_r_iGl_ipGl][ijack];
		
		const qprop_t amp_vert=prop_inv1*vert*quaGamma[5]*prop_inv2.adjoint()*quaGamma[5];
		
		//projecting on quark side
		auto projector=(quaGamma[ipGq]*(quaGamma[0]+g5_sign_of_iproj[iproj]*quaGamma[5])).adjoint();
		out+=(coeff*(amp_vert*projector).trace()).real()/norm;
		
		cout<<" i: "<<i<<", iGq: "<<iGq<<", ipGl: "<<ipGl<<", iproj: "<<iproj<<", im_r_im_r_iGl_ipGl(jverts): "<<im_r_im_r_iGl_ipGl<<", im_r_im_r_iop_iproj(out): "<<im_r_im_r_iop_iproj<<endl;
	      }
	  }
      
      cout<<"amputated, im_fw: "<<im_fw<<", r_fw: "<<r_fw<<", im_bw: "<<im_bw<<", r_bw: "<<r_bw<<", iop: "<<iop<<", iproj: "<<iproj<<", ijack: "<<ijack<<", out: "<<out<<endl;
    }
  
  return pr;
}
