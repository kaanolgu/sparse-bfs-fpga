# Sparse-BFS-FPGA
This work is submitted to the 25th Euromicro Conference on Digital System Design (DSD)

Full paper is now published on IEEEXplore [https://ieeexplore.ieee.org/document/9996632]
## Instructions
One of the following scripts needs to be created on your project directory in order to create neccessary Vivado projects  
For windows : ( Create a .bat file and insert the following commands then run it)
For Linux: (Create a .sh file and run it with following commands)
First tcl argument is the project name and the second argument is the address

### Scripts 
#### run-win.bat (Windows)
```
CALL C:\Xilinx\Vivado\2018.2\bin\vivado.bat -mode batch -source build.tcl -tclargs project_PE0 0x43c00000 
CALL C:\Xilinx\Vivado\2018.2\bin\vivado.bat -mode batch -source build.tcl -tclargs project_PE1 0x43c20000 
PAUSE
```

#### run-lin.sh (Linux)
```
# launch vivado first
vivado -mode batch -source build.tcl -tclargs project_PE0 0x43c00000
vivado -mode batch -source build.tcl -tclargs project_PE1 0x43c20000
```
### Run
These scripts will create the Vivado projects and later on run the "Synthesis" automatically (added feature to the tcl source codes for convenience) 
User needs to do only the following for each PE unit then package these IP blocks.
and then Tools -> Create and Package a New IP -> Package your current project


Import these exported 2 PE blocks to a top level vivado project which could be set up according to the connections in [top level design](top_level_design.pdf) file

Later on you need to export the bitstream files from the top level design and run the project files from Xilinx SDK
## License
The source files for the Sparse BFS used for Zedboard Implementation
[![CC BY 4.0][cc-by-shield]][cc-by]

This work is licensed under a
[Creative Commons Attribution 4.0 International License][cc-by].

[![CC BY 4.0][cc-by-image]][cc-by]

[cc-by]: http://creativecommons.org/licenses/by/4.0/
[cc-by-image]: https://i.creativecommons.org/l/by/4.0/88x31.png
[cc-by-shield]: https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg

## Reference

```
@INPROCEEDINGS{9996632,
  author={Olgu, Kaan and Nikov, Kris and Nunez-Yanez, Jose},
  booktitle={2022 25th Euromicro Conference on Digital System Design (DSD)}, 
  title={Analysis of Graph Processing in Reconfigurable Devices for Edge Computing Applications}, 
  year={2022},
  volume={},
  number={},
  pages={16-23},
  doi={10.1109/DSD57027.2022.00012}}
```
