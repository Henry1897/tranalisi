#ifndef _KL2_IB_FIT_HPP
#define _KL2_IB_FIT_HPP

#include <common.hpp>
#include <fit.hpp>
#include <oper.hpp>

//! index of flag and input_an
extern index_t ind_an;

//! number of analysis to evaluate systematic effects
const size_t nan_syst=8;
//! flag for lattice systematics
const size_t asyst_mask=1;
//! flag for FSE systematics
const size_t fsyst_mask=2;
//! flag for chiral systematics
const size_t csyst_mask=4;

//! get flag for FSE systematics
inline bool FSE_an(size_t an_flag)
{return an_flag & fsyst_mask;}

//! get flag for continuum systematics
inline bool cont_an(size_t an_flag)
{return an_flag & asyst_mask;}

//! get flag for chiral systematics
inline bool chir_an(size_t an_flag)
{return an_flag & csyst_mask;}

dboot_t cont_chir_fit_dM2Pi(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_dM2K_QED(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const dboot_t &ms_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_dM2K_QCD(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_M2Pi0g(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_M2K0g(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_epsilon(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_epsilon_Pi0(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_epsilon_K0(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_linear_fit(const dbvec_t &a,const dbvec_t &z,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,const string &yaxis_label,double apow,double zpow,size_t an_flag,bool with_without_FSE,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_linear_fit_dM(const dbvec_t &a,const dbvec_t &z,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,const string &yaxis_label,double apow,double zpow,size_t an_flag,bool with_without_FSE,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_quad_fit(const dbvec_t &a,const dbvec_t &z,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,const string &yaxis_label,double apow,double zpow,size_t an_flag,bool with_without_FSE,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_constant_fit(const dbvec_t &a,const dbvec_t &z,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,const string &yaxis_label,double apow,double zpow,size_t an_flag,bool with_without_FSE,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_dM2D_QCD(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

dboot_t cont_chir_fit_deltaFK(const dbvec_t &a,const dbvec_t &z,const dboot_t &f0,const dboot_t &B0,const vector<cont_chir_fit_data_t> &ext_data,const dboot_t &ml_phys,const string &path,size_t an_flag,bool cov_flag,const vector<string> &beta_list);

#endif
