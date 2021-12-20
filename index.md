## LSS (Linear System Solvers)

LSS is C++ library written written in Visual Studio 2019 IDE (VS) on win-x64 platform using C++17 standard. It contains several linear system solvers plus some ODE and PDE solvers. 
It also has some output functionalities.

### Requirements

LSS uses among others some CUDA solvers. Therefore NVidia's graphic device with CUDA library v11.3 (and above) is required.

### Dependency

* NVidia's CUDA library v11.3 (and newer)

### Setup

As the library is being developed and tested in VS I will describe the setup only for this IDE. For other IDEs the steps will be similar.

##### 0.Step
Download the library in zip or tar above and extract. 

##### 1.Step
Make sure to create CUDA project (>= v11.3) in VS

##### 2.Step
Open property pages for the newly created project and
1. under Debugging set Environment to point to CUDA binaries folder (in my case it is PATH=C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.3\bin)
2. under VC++ Directories set Include Directories to point to include folder of this library
3. under VC++ Directories set Library Directories to point to lib folder of this library
4. under Linker->Input tab add to Additional Dependencies cusolver.lib;cusparse.lib; cublas.lib; cublasLt.lib;lss_debug.lib (or lss_release.lib in case of Release configuration)
5. under Linker->General tab set Additional Library Dependencies to point to lib folder of this library
6. under CUDA Linker->General tab set Additional Library Directories to point to lib folder of this library

##### 3.Step
Place lss_debug.dll,lss_debug.lib (lss_release.dll, lss_release.lib in case of Release configuration) into your executable folder

##### 4.Step
Now you should be ready to use the library. Test it using following example


```cpp
// main.cu file 


#include <iostream>
#include <string>
#include <lss/utilities/range.hpp>
#include <lss/configs/discretization_config_1d.hpp>


int main()
{

    // number of space subdivisions:
    std::size_t const Sd = 100;
    // number of time subdivisions:
    std::size_t const Td = 100;
    // space range:
    auto const &space_range_ptr = lss::range_builder().lower(0.0).upper(20.0).build();
    // time range
    auto const &time_range_ptr = lss::range_builder().lower(0.0).upper(1.0).build();

    //// discretization config:
    auto const &discretization_ptr = lss::discretization_config_1d_builder()
                                        .space_range(space_range_ptr)
                                        .number_of_space_points(Sd)
                                        .time_range(time_range_ptr)
                                        .number_of_time_points(Td)
                                        .build();

    std::cout<<"Uniform space step value: "<< discretization_ptr->space_step()<<"\n";

    return 0;
}
```
If it does not compile or run ok make sure you did not miss any of the previous steps. Otherwise you can drop me a line on my github page.


### Contents

In this section I will try to describe how to work with the library on several examples. I will also list several conventions which a client has to follow in order to properly use the solvers inside the library. Some of these conventions will be relaxed as the developement progresses.







You can use the [editor on GitHub](https://github.com/MichalSara99/lss/edit/gh-pages/index.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/MichalSara99/lss/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
