## Boundary and initial/terminal conditions conventions

### Boundary Conditions

LSS supports three types of boundary conditions: **Dirichlet**, **Neumann** and **Robin**. All solvers except for specific ones (so far only Heston type) allow any combination of these. 

### ODE Solvers
In what follows ![solution_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20u%28x_%7B0%7D%29%20%7D) represents a solution of an ODE and ![boundary_point_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20x_%7B0%7D%20%7D) represents a point in which we evaluate a boundary condition. Let us consider following simple 2nd order ODE

![ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20%5Cfrac%7Bd%5E%7B2%7Du%28x%29%7D%7Bdx%5E%7B2%7D%7D%3D-2%20%7D)



#### Dirichlet Boundary
  
LSS assumes Dirichlet boundary of following form
  
 ![dirichlet_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20u%28x_%7B0%7D%29%20%3D%20A%7D)

Specifically, if we have following Dirichlet boundary:

![dirichlat_exampl_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20u%28x_%7B0%7D%29%20%3D%203.1415%7D)

then in code we write:

```cpp
  #include <lss/boundary/dirichlet_1d.hpp>

  auto const dirichlet =  3.1415; 
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::dirichlet_1d_builder().value(dirichlet).build();

```
 
  
#### Neumann Boundary

LSS assumes Neumann boundary of following form

 ![neumann_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20&plus;%20A%20%3D%200%7D)
 
Specifically, if we have following Neumann boundary:

![neumann_exampl_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20%3D%201%7D)

then in code we write:

```cpp
  #include <lss/boundary/neumann_1d.hpp>

  auto const neumann = -1.0;
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::neumann_1d_builder().value(neumann).build();

```

Note *-1.0* rather then *1.0*. We must pay attention to the aforementioned convention or we get completely different solution.

#### Robin Boundary

LSS assumes Robin boundary of following form

 ![robin_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20&plus;%20Au%28x_%7B0%7D%29%20&plus;%20B%20%3D%200%7D)

Specifically, if we have following Robin boundary:

![robin_exampl_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20&plus;%202u%28x_%7B0%7D%29%20%3D%200%7D)

then in code we write:

```cpp
  #include <lss/boundary/robin_1d.hpp>

  auto const robin_first =  2.0; 
  auto const robin_second =  0.0;
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::robin_1d_builder()
                                  .values(robin_first,robin_second)
                                  .build();

```

### 1D PDE Solvers

In what follows ![solution_1d_pde](https://latex.codecogs.com/gif.latex?%5Cinline%20%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20u%28t%2Cx%29%7D) represents a solution of 1D PDE and ![boundary_point_1d_pde](https://latex.codecogs.com/gif.latex?%5Cinline%20%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20x_%7B0%7D%7D) represents a point in which we evaluate a boundary condition and ![initial_point_1d_pde](https://latex.codecogs.com/gif.latex?%5Cinline%20%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20t_%7B0%7D%7D) represents a time at which we evaluate an initial/terminal condition. Let us consider following 1D PDE (heat equation)

![pde_1d](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7B%5Cpartial%20u%28t%2Cx%29%7D%7B%5Cpartial%20t%7D%20%3D%20%5Cfrac%7B%5Cpartial%5E%7B2%7Du%28t%2Cx%29%7D%7B%5Cpartial%20x%5E%7B2%7D%7D%7D)



#### Dirichlet Boundary
  
LSS assumes Dirichlet boundary of following form
  
 ![dirichlet_1d_pde](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20u%28t%2Cx_%7B0%7D%29%20%3D%20A%28t%29%7D)

Specifically, if we have following Dirichlet boundary:

![dirichlet_exampl_1d_pde](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20u%28t%2Cx_%7B0%7D%29%20%3D%202*t%7D)

then in code we write:

```cpp
  #include <lss/boundary/dirichlet_1d.hpp>

  auto const &dirichlet = [](double t) { return 2*t; }; 
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::dirichlet_1d_builder().value(dirichlet).build();

```
 
  
#### Neumann Boundary

LSS assumes Neumann boundary of following form

 ![neumann_1d_pde](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7B%5Cpartial%20u%28t%2Cx_%7B0%7D%29%7D%7B%5Cpartial%20x%7D%20&plus;%20A%28t%29%20%3D%200%7D)
 
Specifically, if we have following Neumann boundary:

![neumann_exampl_1d_pde](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7B%5Cpartial%20u%28t%2Cx_%7B0%7D%29%7D%7B%5Cpartial%20x%7D%20%3D%202t%7D)

then in code we write:

```cpp
  #include <lss/boundary/neumann_1d.hpp>

  auto const neumann = [](double t) { return -2*t; }; 
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::neumann_1d_builder().value(neumann).build();

```

Note *-1.0* rather then *1.0*. We must pay attention to the aforementioned convention or we get completely different solution.

#### Robin Boundary

LSS assumes Robin boundary of following form

 ![robin_1d_pde](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7B%5Cpartial%20u%28t%2Cx_%7B0%7D%29%7D%7B%5Cpartial%20x%7D%20&plus;%20A%28t%29u%28t%2Cx_%7B0%7D%29%20&plus;%20B%28t%29%20%3D%200%7D)

Specifically, if we have following Robin boundary:

![robin_exampl_1d_pde](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B240%2C240%2C240%7D%20%5Cfrac%7B%5Cpartial%20u%28t%2Cx_%7B0%7D%29%7D%7B%5Cpartial%20x%7D%20&plus;%202tu%28t%2Cx_%7B0%7D%29%20%3D%200%7D)

then in code we write:

```cpp
  #include <lss/boundary/robin_1d.hpp>

  auto const robin_first =  [](double t) { return 2*t; }; 
  auto const robin_second = [](double t) { return 0.0; };
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::robin_1d_builder()
                                  .values(robin_first,robin_second)
                                  .build();

```

#### Initial/Terminal Contidion

TBC
