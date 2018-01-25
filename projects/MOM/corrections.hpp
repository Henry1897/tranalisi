#ifndef _CORRECTIONS_HPP
#define _CORRECTIONS_HPP

#include <geometry.hpp>
#include <oper.hpp>
#include <Zbil.hpp>

#ifndef EXTERN_CORRECTIONS
 #define EXTERN_CORRECTIONS extern
 #define INIT_TO(...)
#else
 #define INIT_TO(...) = __VA_ARGS__
#endif

namespace gaz
{
  enum type_t{PLAQ,TLSYM,IWA};
  const map<string,type_t> decr={{"Plaq",PLAQ},{"tlSym",TLSYM},{"Iwa",IWA}};
  const size_t n=3;
  PROVIDE_DECRYPTER;
}

namespace gf
{
  enum type_t{FEYNMAN,LANDAU};
  const map<string,type_t> decr={{"Feynman",FEYNMAN},{"Landau",LANDAU}};
  const size_t n=2;
  PROVIDE_DECRYPTER;
  const double lambda[2]={1.0,0.0};
}

const valarray<double> c1={0,-1.0/12,-0.331};
const valarray<double> c0=1.0-8.0*c1;
const valarray<double> C2=c1;

const double Eps0[gaz::n][4]=
  {{0.0,16.6444139,-2.24886853,-1.39726711},
   {0.0,13.02327272,-2.01542504,-1.24220271},
   {0.0,8.1165665,-1.60101088,-0.97320689}};

const double Eps1[gaz::n][4]=
  {{0.0,12.8269254,-5.20234231,-0.08172763},
   {0.0,10.69642966,-4.7529781,-0.075931174},
   {0.0,7.40724287,-3.88883584,-0.061025650}};

const double Eps2[gaz::n][7]=
  {{0.0,-4.74536466,0.02028705,0.10348577,-1.5048070,0.70358496,0.534320852},
   {0.0,-4.2478783,0.05136635,0.07865292,-1.14716212,0.65343092,0.49783419},
   {0.0,-3.2018047,0.08249970,0.04192446,-0.6202244,0.55587473,0.41846440}};

const double Epstilde1[gaz::n][4]=
  {{0.0,9.174787621,4.5873938103,-1.5291312701},
   {0.0,7.071174701,3.535587351,-1.1785291169},
   {0.0,4.423664730,2.211832365,-0.7372774550}};

const double Epstilde2[gaz::n][4]=
  {{0.0,7.4696262,8.2395316,-3.21623339},
   {0.0,5.95209802,7.16084231,-3.0693492},
   {0.0,3.6929018,5.19541051,-2.4645273}};

const double EpsS0[gaz::n][4]=
  {{0.0,0.30799634,9.9867847,0.01688643},
   {0.0,0.58345905,8.8507071,-0.12521126},
   {0.0,0.74092360,6.9016820,-0.29335071}};

const double EpsS1[gaz::n][4]=
  {{0.0,0.6586287,-4.20298580,-1.286053869},
   {0.0,0.33939970,-3.76353718,-1.150059945},
   {0.0,-0.05097214,-2.88571027,-0.909503374}};

const double EpsS2[gaz::n][4]=
  {{0.0,2.60041308,-4.15080331,0.17641091},
   {0.0,2.3547298,-3.85277871,0.196461884},
   {0.0,2.02123300,-3.23459547,0.234502732}};

const double EpsP0[gaz::n][3]=
  {{0.0,9.95102761,3.43328275},
   {0.0,8.7100837,2.98705498},
   {0.0,6.55611308,2.25383382}};

const double EpsP2[gaz::n][3]=
  {{0.0,0.84419938,-0.25823485},
   {0.0,0.70640549,-0.27556247},
   {0.0,0.66990790,-0.30221183}};

const double EpsV0[gaz::n][4]=
  {{0.0,3.97338480,-2.49669620,0.85409908},
   {0.0,3.57961385,-2.21267683,0.77806655},
   {0.0,2.98283189,-1.72542048,0.63679613}};

const double EpsV1[gaz::n][4]=
  {{0.0,2.7109817,-1.84813992,-0.39052850},
   {0.0,2.09743725,-1.51877201,-0.385127257},
   {0.0,0.9074321,-0.80352187,-0.356005234}};

const double EpsV2[gaz::n][10]=
  {{0.0,1.5541024,0.32907377,-0.0060202576,0.2500659,0.8859920,-0.300364436,1.27887765,0.27776135,-0.35475044},
   {0.0,1.6762868,0.22601986,0.02822949,0.0214112,0.8342659,-0.28736163,1.03773908,0.28969451,-0.302816648},
   {0.0,1.4573118,0.0858961,0.07934994,-0.2668492,0.712786719,-0.25078366,0.76263373,0.29755270,-0.184270928}};

const double EpsA0[gaz::n][2]=
  {{0.0,-0.84813073},
    {0.0,-0.48369852},
   {0.0,0.0752372}};

const double EpsA1[gaz::n][4]=
  {{0.0,1.34274645,-1.71809242,0.130176166},
    {0.0,0.92541220,-1.54604828,0.128375752},
   {0.0,0.2684958,-1.238019617,0.1186684108}};

const double EpsA2[gaz::n][10]=
  {{0.0,0.3879068,1.85116980,-0.093094486,1.6350438,-1.59945524,0.333900263,0.41758917,0.395847810,0.31972188},
    {0.0,0.29616583,1.7629637,-0.11136345,1.3008790,-1.48761993,0.314172576,0.596637529,0.33473715,0.27870681},
   {0.0,0.05917686,1.5707047,-0.13932655,0.6845753,-1.24800562,0.26827353,1.05772129,0.18672220,0.17428813}};

const double EpsT0[gaz::n][4]=
  {{0.0,0.37366536,-1.66446414,-0.5750281973},
    {0.0,0.51501972,-1.47511786,-0.4769739579},
   {0.0,0.82253993,-1.15028034,-0.3267471901}};

const double EpsT1[gaz::n][4]=
  {{0.0,-4.05372833,1.866287582,-0.8573692476},
    {0.0,-3.0228493,1.59558642,-0.7667066321},
   {0.0,-1.17592792,1.087913642,-0.6063355831}};

const double EpsT2[gaz::n][10]=
  {{0.0,2.3328621,-1.52209604,0.23683195,-2.02795509,0.11808647,0.07250824,0.3932905,1.10184617,-0.02744360},
   {0.0,2.4912319,-1.53694399,0.26295051,-1.55221265,0.04504264,0.07020813,0.1467998,1.03762644,-0.03500219},
   {0.0,2.3441345,-1.4848088,0.30172406,-0.6509124,-0.11083048,0.06071268,-0.2049940,0.88259379,-0.04896801}};

const double EpsT2prime[gaz::n][10]=
  {{0.0,0.00047095,0.0,0.0,-0.30537822,0.0,0.0,1.4070324,0.28175492,0.054718244},
   {0.0,-0.26900984,0.0,0.0,-0.67000961,0.0,0.0,1.0574111,0.24663315,0.06136902},
   {0.0,-0.45213470,0.0,0.0,-1.24108756,0.0,0.0,0.3465297,0.19560470,0.07153771}};

namespace group
{
  enum type_t{U1,SU3};
  const size_t n=2;
}

//! build a generic correction in terms of invariant and coeffs
inline double corr_a2(group::type_t group,double p2,double p4,double *c)
{
  double Cf[2]={1.0,4.0/3};
  
  return Cf[group]*(p2*(c[0]+c[1]*log(p2))+c[2]*p4/p2)/(16*sqr(M_PI));
}

//! corrections to sigma1,in units of g^2
inline double sig1_a2(gaz::type_t iaz,gf::type_t gf_g,group::type_t group,const imom_t &ip,const coords_t &L)
{
  double lambda=gf::lambda[gf_g];
  
  p_t p_tilde=ip.p(L).tilde();
  double p2_tilde=p_tilde.norm2(),p4_tilde=p_tilde.norm4();
  
  const double Np=ip.Np();
  double cq[3];
  cq[0]=-Eps2[iaz][4]-lambda*1.51604667-(Eps2[iaz][1]+lambda*0.507001567+Eps0[iaz][1]/6.0-lambda/6.0*4.79200956)/Np;
  cq[1]=-(59.0/240.0+c1[iaz]/2+C2[iaz]/60.0-lambda*3.0/8.0)-(101.0/120.0-11.0/30.0*C2[iaz])/Np;
  cq[2]=3.0/80.0+C2[iaz]/10.0+lambda*5.0/48.0;
  
  return corr_a2(group,p2_tilde,p4_tilde,cq);
}

//! coefficients of Zbil
EXTERN_CORRECTIONS double pr_bil_a2_c[nZbil][3];

//! set all coefficients for bilinears
void set_pr_bil_a2(gaz::type_t iaz,gf::type_t gf_g);

//! corrections to projected,in units of g^2
inline double pr_bil_a2(gaz::type_t iaz,gf::type_t gf_g,group::type_t group,const imom_t &ip,const coords_t &L,size_t iZ)
{
  p_t p_tilde=ip.p(L).tilde();
  double p2_tilde=p_tilde.norm2(),p4_tilde=p_tilde.norm4();
  
  //set the coefficients
  set_pr_bil_a2(iaz,gf_g);
  
  return corr_a2(group,p2_tilde,p4_tilde,pr_bil_a2_c[iZ]);
}

#undef EXTERN_CORRECTIONS
#undef INIT_TO

#endif
