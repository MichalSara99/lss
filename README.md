# LSS (Linear System Solvers)
Linear System Solvers library. Written in C++17. It contains a few wrappers around CUDA cuSolver library functions plus some other well known solvers.
It also contains some ODE and PDE solvers.

## ODE Solver
* general 2nd degree two-point equation with variable coefficients (supports all Dirichlet, Neumann, Robin boundary conditions)
* All solvers support uniform and non-uniform grid with variable scaling


## PDE Solver
* 1D general heat equation with variable coefficients (in space and time dimension) (supports all Dirichlet, Neumann, Robin boundary conditions)
* 1D general wave equation with variable coefficients (in space and time dimension) (supports all Dirichlet, Neumann, Robin boundary conditions)
* 2D general Heston type model with variable coefficients (in space and time dimension)
 (support for Douglas-Rachford ADI, Craig-Sneyd ADI, Modified Craig-Sneyd ADI, Hundsdorfer-Verwer ADI)
* All solvers support uniform and non-uniform grid with variable scaling

## Usage
# Visual Studio:

0. make sure to create CUDA project (>= v11.3) in VS
1. open property pages for the newly created project
   1. under Debugging set Environment to point to CUDA binaries folder (in my case it is PATH=C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.3\bin\)
   2. under VC++ Directories set Include Directories to point to include folder of this library
   3. under VC++ Directories set Library Directories to point to lib folder of this library
   4. under Linker|Input add to Additional Dependencies cusolver.lib;cusparse.lib; cublas.lib; cublasLt.lib;lss_debug.lib (or lss_release.lib in case of Release configuration)
   5. under Linker|General set Additional Library Dependencies to point to lib folder of this library
   6. under CUDA Linker|General set Additional Library Directories to point to lib folder of this library
2. place lss_debug.dll,lss_debug.lib (lss_release.dll, lss_release.lib in case of Release configuration) into your executable folder
3. now you should be ready to use the library

## Output
* results can be put into stream or xml. Folder output also contains some python scripts that parse the resulting xmls and plot the solutions. 

## Requirement
* Library is being developed in VS2019 for win-x64 arch
* NVIDIA CUDA lib >= v11.3

## Some curves from ODE solver
Simple Two-point BVP (u''(x) = -2 with Dirichlet and Robin BC)
![Simple ODE equation](/outputs/pics/simple_ode_numerical.png)

## Some surfaces from PDE solver

Heat equation (Dirichlet BC) from implicit solver
![Pure heat equation](/outputs/pics/temp_heat_equ_numerical_nonuniform.png)

Wave equation (Dirichlet BC) from implicit solver
![Pure wave equation](/outputs/pics/wave_pure_dir_equ_numerical.png)

Wave equation (Neumann BC) from implicit solver
![Pure wave equation - neumann](/outputs/pics/wave_neu_equ_numerical.png)

Damped wave equation (Dirichlet BC) from implicit solver
![Damped wave equation](/outputs/pics/damped_wave_dir_equ_numerical.png)

Heat equation (Dirichlet and Neumann BC) from explicit solver
![Pure heat equation](/outputs/pics/temp_heat_neu_equ_numerical.png)

Advection equation from implicit solver
![Advection equation](/outputs/pics/temp_advection_equ_numerical.png)

Black-Scholes equation from implicit solver
![Black-Scholes equation](/outputs/pics/call_option_price_surface_numerical_nonuniform.png)

Heston equation DR from implicit solver
![Heston equation DR](/outputs/pics/impl_heston_dr_numerical.png)

Heston equation CS from implicit solver
![Heston equation CS](/outputs/pics/impl_heston_cs_numerical.png)

Heston equation MCS from implicit solver
![Heston equation MCS](/outputs/pics/impl_heston_mcs_numerical.png)

Heston equation HV from implicit solver
![Heston equation HV](/outputs/pics/impl_heston_hv_numerical.png)

SABR equation from implicit solver
![SABR equation](/outputs/pics/impl_sabr_dr_numerical.png)

Heston equation from explicit solver
![Heston equation expl](/outputs/pics/expl_heston_euler_host_numerical.png)

SABR equation from explicit solver
![SABR equation expl](/outputs/pics/expl_sabr_euler_host_numerical.png)
