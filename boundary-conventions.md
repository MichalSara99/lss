## Boundary and initial/terminal conditions conventions

### Boundary Conditions

LSS supports three types of boundary conditions: **Dirichlet**, **Neumann** and **Robin**. All solvers except for specific ones (so far only Heston type) allow any combination of these. 

### ODE Solvers
In what follows ![solution_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20u%28x_%7B0%7D%29%20%7D) represents a solution of an ODE and ![boundary_point_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20x_%7B0%7D%20%7D) represents a point in which we evaluate a boundary condition. Let us consider following simple 2nd order ODE

![ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20%5Cfrac%7Bd%5E%7B2%7Du%28x%29%7D%7Bdx%5E%7B2%7D%7D%3D-2%20%7D)



#### Dirichlet Boundary
  
LSS assumes Dirichlet boundary of following form
  
 ![dirichlet_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20u%28x_%7B0%7D%29%20%3D%20A%28t%29%7D)

Specifically, if we have following Dirichlet boundary:

![dirichlat_exampl_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20u%28x_%7B0%7D%29%20%3D%20t%20%7D)

then in code we write:

```cpp
  #include <lss/boundary/dirichlet_1d.hpp>

  auto const &dirichlet = [](double t) { return t; };
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::dirichlet_1d_builder().value(dirichlet).build();

```
 
  
#### Neumann Boundary

LSS assumes Neumann boundary of following form

 ![neumann_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20&plus;%20A%28t%29%20%3D%200%20%7D)
 
Specifically, if we have following Neumann boundary:

![neumann_exampl_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20%3D%201%20%7D)

then in code we write:

```cpp
  #include <lss/boundary/neumann_1d.hpp>

  auto const &neumann = [](double t) { return -1.0; };
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::neumann_1d_builder().value(neumann).build();

```

Note *-1.0* inside the lambda rather then *1.0*. We must pay attention to the aforementioned convention or we get completely different solution.

#### Robin Boundary

LSS assumes Robin boundary of following form

 ![robin_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20&plus;%20A%28t%29u%28x_%7B0%7D%29%20&plus;%20B%28t%29%20%3D%200%20%7D)

Specifically, if we have following Robin boundary:

![robin_exampl_ode](https://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20%7B%5Ccolor%5BRGB%5D%7B200%2C200%2C200%7D%20%5Cfrac%7Bdu%28x_%7B0%7D%29%7D%7Bdx%7D%20&plus;%202u%28x_%7B0%7D%29%20%3D%200%20%7D)

then in code we write:

```cpp
  #include <lss/boundary/robin_1d.hpp>

  auto const &robin_first = [](double t) { return 2.0; };
  auto const &robin_second = [](double t) { return 0.0; };
  
  // build boundary conditions from above function:
  auto const &boundary_ptr = lss::robin_1d_builder()
                                  .linear_value(robin_first)
                                  .value(robin_second)
                                  .build();

```

### 1D PDE Solvers

TBC later

