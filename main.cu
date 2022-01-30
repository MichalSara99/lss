#include<iostream>
#include<string>

#include"unit_tests/sparse_solvers/lss_core_cuda_solver_t.hpp"
#include"unit_tests/ode_solvers/second_degree/lss_odes_2_degree_t.hpp"
#include"unit_tests/pde_solvers/1d/lss_advection_equation_t.hpp"
#include"unit_tests/pde_solvers/1d/lss_black_scholes_equation_t.hpp"
#include"unit_tests/pde_solvers/1d/lss_pure_heat_equation_t.hpp"
#include"unit_tests/pde_solvers/1d/lss_pure_wave_equation_t.hpp"
#include"unit_tests/pde_solvers/2d/lss_heston_equation_t.hpp"
#include"unit_tests/pde_solvers/3d/lss_hhw_equation_t.hpp"
#include"unit_tests/pde_solvers/2d/lss_sabr_equation_t.hpp"
#include"unit_tests/common/lss_xml_t.hpp"
#include"unit_tests/common/lss_container_3d_t.hpp"

int main()
{
     // ======================================================
     // =============== lss_container_3d_t ===================
     // ======================================================
     // basic_rcontainer_3d_test();
     // slice_rcontainer_3d_test(); 
     // basic_ccontainer_3d_test();
     // slice_ccontainer_3d_test();  
     // basic_lcontainer_3d_test();

     // ======================================================
     // =============== lss_odes_2_degree_t ==================
     // ======================================================
     // test_impl_simple_ode_dirichlet_bc_cuda_solver_device();
     // test_impl_simple_ode_dirichlet_neumann_bc_cuda_solver_device();
     // test_impl_simple_ode_dirichlet_robin_bc_cuda_solver_device();
     // test_impl_simple_ode_neumann_robin_bc_cuda_solver_device();
     // test_impl_simple_ode1_neumann_robin_bc_cuda_solver_device();

    // ======================================================
    // ============= lss_core_cuda_solver_t =================
    // ======================================================
    // test_device_sparse_qr();
    // test_host_sparse_qr_test();
    // test_dirichlet_bc_bvp_on_host();
    // test_dirichlet_bc_bvp_on_device();
    // test_robin_bc_bvp_on_host();
    // test_robin_bc_bvp_on_device();

    // ======================================================

    // ======================================================
    // ============= lss_core_cuda_solver_t =================
    // ======================================================
    // test_impl_simple_ode_dirichlet_bc_cuda_solver_device();
    // test_impl_simple_ode_dirichlet_neumann_bc_cuda_solver_device();
    // test_impl_simple_ode_dirichlet_robin_bc_cuda_solver_device();
    // test_impl_simple_ode_neumann_robin_bc_cuda_solver_device();
    // test_impl_simple_ode1_neumann_robin_bc_cuda_solver_device();

    // ======================================================


    // ======================================================
    // =========== lss_advection_equation_t =================
    // ======================================================
    // test_impl_adv_diff_equation_dirichlet_bc_cuda_solver_device_qr();
    // test_impl_adv_diff_equation_dirichlet_bc_sor_solver_device();
    // test_impl_adv_diff_equation_dirichlet_bc_sor_solver_host();
    // test_impl_adv_diff_equation_dirichlet_bc_cuda_solver_host_qr();
    // test_impl_adv_diff_equation_dirichlet_bc_double_sweep_solver();
    // test_impl_adv_diff_equation_dirichlet_bc_thomas_lu_solver();

    // ======================================================

    // ======================================================
    // =========== lss_black_scholes_equation_t =============
    // ======================================================
    // test_impl_black_scholes_equation_dirichlet_bc_cuda_solver_device_qr();
    // test_impl_black_scholes_equation_dirichlet_bc_sor_solver_device();
    // test_impl_black_scholes_equation_dirichlet_bc_sor_solver_host();
    // test_impl_black_scholes_equation_dirichlet_bc_double_sweep_solver();
    // test_impl_black_scholes_equation_dirichlet_bc_thomas_lu_solver();
    // test_impl_fwd_black_scholes_equation_dirichlet_bc_cuda_solver_device_qr();
    // test_impl_black_scholes_equation_dirichlet_bc_thomas_lu_solver_stepping();
    // test_expl_black_scholes_equation_dirichlet_bc_ade();
    // 
    // ======================================================

    // ======================================================
    // ================== lss_pure_heat_equation_t ==========
    // ======================================================
    // test_impl_pure_heat_equation_dirichlet_bc_cuda_solver_device_qr();
    // test_impl_pure_heat_equation_dirichlet_bc_sor_solver_device();
    // test_impl_pure_heat_equation_dirichlet_bc_sor_solver_host();
    // test_impl_pure_heat_equation_dirichlet_bc_cuda_solver_host_qr();
    // test_impl_pure_heat_equation_dirichlet_bc_double_sweep_solver();
    // test_impl_pure_heat_equation_dirichlet_bc_thomas_lu_solver();
    // test_impl_pure_heat_equation_neumann_bc_cuda_solver_device_qr();
    // test_impl_pure_heat_equation_neumann_bc_thomas_lu_solver();
    // test_impl_pure_heat_equation_neumann_bc_double_sweep_solver();
    // test_impl_pure_heat_equation_dirichlet_bc_cuda_solver_device_qr_stepping();
    // test_impl_pure_heat_equation_source_dirichlet_bc_cuda_solver_device();
    // test_impl_pure_heat_equation_source_dirichlet_bc_sor_solver_device();
    // 
    // test_expl_pure_heat_equation_dirichlet_bc_ade();
    // test_expl_pure_heat_equation_neumann_bc_euler();
    // test_expl_pure_heat_equation_dirichlet_bc_device();
    // ======================================================

    // ======================================================
    // =============== lss_pure_wave_equation_t =============
    // ======================================================
    // test_impl_pure_wave_equation_dirichlet_bc_cuda_solver_device_qr();
    // test_impl_pure_wave_equation_dirichlet_bc_cuda_solver_device_sor();
    // test_impl_pure_wave_equation_dirichlet_bc_cuda_solver_host_sor();
    // test_impl_pure_wave_equation_dirichlet_bc_solver_host_double_sweep();
    // test_impl_pure_wave_equation_dirichlet_bc_solver_host_lu();
    // test_impl_wave_equation_dirichlet_bc_solver_host_lu();
    // test_impl_damped_wave_equation_dirichlet_bc_solver_host_double_sweep();
    // test_impl_pure_wave_equation_neumann_bc_cuda_solver_device_qr();
    // test_expl_pure_wave_equation_dirichlet_bc_cuda_host_solver();
    // test_expl_pure_wave_equation_dirichlet_bc_cuda_device_solver();
    // 
    // ======================================================

    // ======================================================
    // =============== lss_heston_equation_t ================
    // ======================================================
    // test_impl_heston_equation_cuda_qr_solver();
    // test_impl_heston_equation_thomas_lu_solver();
    //
    // ======================================================

    // ======================================================
    // ================= lss_sabr_equation_t ================
    // ======================================================
    // test_impl_sabr_equation_double_sweep_solver();
    //
    // ======================================================

    // ======================================================
    // ================== lss_hhw_equation_t ================
    // ======================================================
    // test_impl_hhw_equation_cuda_qr_solver();
    // test_impl_hhw_equation_tlu_dss_solver();  
    // 
    // ======================================================

    // ======================================================
    // ====================== lss_xml_t =====================
    // ======================================================
    // test_impl_simple_ode_thomes_lu_qr_xml();
    // test_impl_bs_thomas_lu_crv_xml();
    // test_impl_bs_thomas_lu_srf_xml();
    // test_impl_ph_dirichlet_bvp_device_qr_srf_xml();
    // test_expl_ph_neumann_bvp_euler_srf_xml();
    // test_impl_adv_thomas_lu_srf_xml();
    // test_impl_pw_dirichlet_bvp_cuda_device_qr_srf_xml();
    // test_impl_w_dirichlet_bvp_host_lu_srf_xml();
    // test_impl_w_bvp_host_dss_srf_xml();
    // test_impl_pw_neumann_bvp_cuda_device_qr_srf_xml();
    // test_expl_pw_dirichlet_bvp_cuda_host_host_srf_xml();
    // test_impl_heston_cuda_qr_cn_dr_srf_xml();
    // test_impl_heston_thomas_lu_cn_srf_xml();
    // test_impl_sabr_double_sweep_cn_srf_xml();
    // test_impl_heston_thomas_lu_dr_cn_srf_xml();
    // test_impl_heston_dss_cs_cn_srf_xml();
    // test_impl_heston_thomas_lu_mcs_cn_srf_xml();
    // test_impl_heston_thomas_lu_hw_cn_srf_xml();
    // test_expl_heston_host_euler_srf_xml();
    // test_expl_heston_device_euler_srf_xml();
    // test_expl_sabr_host_euler_srf_xml();
    // test_expl_sabr_device_euler_srf_xml();
    
    //
    // ======================================================

    std::cin.get();
    std::cin.get();
    return 0;
}

