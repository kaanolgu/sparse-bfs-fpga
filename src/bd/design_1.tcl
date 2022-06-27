
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################
#*****************************************************************************************
#   
#    Modifications to include -tclargs done by
#    Kaan Olgu <kaan.olgu@bristol.ac.uk>
#*****************************************************************************************

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2018.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xc7z020clg484-1
   set_property BOARD_PART em.avnet.com:zed:part0:1.4 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
   return $nRet
}

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
ntnueecs:maltanar:AXIInputRegisters:1.0\
ntnueecs:maltanar:AXIOutputRegisters:1.0\
user.org:user:SparseFrontierBackend:1.0\
xilinx.com:ip:xlslice:1.0\
user.org:user:StateProfiler:1.0\
xilinx.com:ip:xlconcat:2.1\
xilinx.com:ip:axis_data_fifo:1.1\
xilinx.com:ip:axis_switch:1.1\
user.org:user:SparseFrontierFrontend:1.0\
xilinx.com:ip:xlconstant:1.1\
user.org:user:LevelGenerator:1.0\
xilinx.com:ip:blk_mem_gen:8.4\
xilinx.com:ip:util_vector_logic:2.0\
xilinx.com:ip:util_reduced_logic:2.0\
"

   set list_ips_missing ""
   common::send_msg_id "BD_TCL-006" "INFO" "Checking if the following IPs exist in the project's IP catalog: $list_check_ips ."

   foreach ip_vlnv $list_check_ips {
      set ip_obj [get_ipdefs -all $ip_vlnv]
      if { $ip_obj eq "" } {
         lappend list_ips_missing $ip_vlnv
      }
   }

   if { $list_ips_missing ne "" } {
      catch {common::send_msg_id "BD_TCL-115" "ERROR" "The following IPs are not found in the IP Catalog:\n  $list_ips_missing\n\nResolution: Please add the repository containing the IP(s) to the project." }
      set bCheckIPsPassed 0
   }

}

if { $bCheckIPsPassed != 1 } {
  common::send_msg_id "BD_TCL-1003" "WARNING" "Will not continue with creation of design due to the error(s) above."
  return 3
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {
  variable AXI_OUTPUT_BASEADDR
  variable AXI_INPUT_BASEADDR
  
  
  set AXI_INPUT_BASEADDR  $::M_AXI_32_BASE_ADDR
  set AXI_OUTPUT_BASEADDR [expr $AXI_INPUT_BASEADDR + 0x1000]								

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set M_AXI_32 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_32 ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {32} \
   CONFIG.DATA_WIDTH {32} \
   CONFIG.FREQ_HZ {100000000} \
   CONFIG.HAS_REGION {0} \
   CONFIG.NUM_READ_OUTSTANDING {2} \
   CONFIG.NUM_WRITE_OUTSTANDING {2} \
   CONFIG.PROTOCOL {AXI4} \
   ] $M_AXI_32
  set M_AXI_64 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_64 ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {32} \
   CONFIG.DATA_WIDTH {64} \
   CONFIG.HAS_BRESP {0} \
   CONFIG.HAS_BURST {0} \
   CONFIG.HAS_CACHE {0} \
   CONFIG.HAS_LOCK {0} \
   CONFIG.HAS_PROT {0} \
   CONFIG.HAS_QOS {0} \
   CONFIG.HAS_REGION {0} \
   CONFIG.HAS_WSTRB {0} \
   CONFIG.NUM_READ_OUTSTANDING {2} \
   CONFIG.NUM_WRITE_OUTSTANDING {2} \
   CONFIG.PROTOCOL {AXI4} \
   CONFIG.READ_WRITE_MODE {READ_ONLY} \
   ] $M_AXI_64
  set S00_AXI [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S00_AXI ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {32} \
   CONFIG.ARUSER_WIDTH {0} \
   CONFIG.AWUSER_WIDTH {0} \
   CONFIG.BUSER_WIDTH {0} \
   CONFIG.DATA_WIDTH {32} \
   CONFIG.FREQ_HZ {100000000} \
   CONFIG.HAS_BRESP {1} \
   CONFIG.HAS_BURST {1} \
   CONFIG.HAS_CACHE {1} \
   CONFIG.HAS_LOCK {1} \
   CONFIG.HAS_PROT {1} \
   CONFIG.HAS_QOS {1} \
   CONFIG.HAS_REGION {0} \
   CONFIG.HAS_RRESP {1} \
   CONFIG.HAS_WSTRB {1} \
   CONFIG.ID_WIDTH {12} \
   CONFIG.MAX_BURST_LENGTH {256} \
   CONFIG.NUM_READ_OUTSTANDING {2} \
   CONFIG.NUM_READ_THREADS {1} \
   CONFIG.NUM_WRITE_OUTSTANDING {2} \
   CONFIG.NUM_WRITE_THREADS {1} \
   CONFIG.PROTOCOL {AXI4} \
   CONFIG.READ_WRITE_MODE {READ_WRITE} \
   CONFIG.RUSER_BITS_PER_BYTE {0} \
   CONFIG.RUSER_WIDTH {0} \
   CONFIG.SUPPORTS_NARROW_BURST {1} \
   CONFIG.WUSER_BITS_PER_BYTE {0} \
   CONFIG.WUSER_WIDTH {0} \
   ] $S00_AXI

  # Create ports
  set clk [ create_bd_port -dir I -type clk clk ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {100000000} \
 ] $clk
  set reset [ create_bd_port -dir I -type rst reset ]
  set_property -dict [ list \
   CONFIG.POLARITY {ACTIVE_HIGH} \
 ] $reset

  # Create instance: AXIInputRegisters_0, and set properties
  set AXIInputRegisters_0 [ create_bd_cell -type ip -vlnv ntnueecs:maltanar:AXIInputRegisters:1.0 AXIInputRegisters_0 ]

  # Create instance: AXIOutputRegisters_0, and set properties
  set AXIOutputRegisters_0 [ create_bd_cell -type ip -vlnv ntnueecs:maltanar:AXIOutputRegisters:1.0 AXIOutputRegisters_0 ]

  # Create instance: Backend, and set properties
  set Backend [ create_bd_cell -type ip -vlnv user.org:user:SparseFrontierBackend:1.0 Backend ]

  # Create instance: BackendProfileSel, and set properties
  set BackendProfileSel [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 BackendProfileSel ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {2} \
   CONFIG.DOUT_WIDTH {3} \
 ] $BackendProfileSel

  # Create instance: BackendProfiler, and set properties
  set BackendProfiler [ create_bd_cell -type ip -vlnv user.org:user:StateProfiler:1.0 BackendProfiler ]

  # Create instance: BackendStart, and set properties
  set BackendStart [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 BackendStart ]

  # Create instance: BigFIFODataCounts, and set properties
  set BigFIFODataCounts [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 BigFIFODataCounts ]
  set_property -dict [ list \
   CONFIG.IN0_WIDTH {10} \
   CONFIG.IN1_WIDTH {10} \
   CONFIG.IN2_WIDTH {10} \
   CONFIG.IN3_WIDTH {8} \
   CONFIG.NUM_PORTS {3} \
 ] $BigFIFODataCounts

  # Create instance: ColPtrFIFO, and set properties
  set ColPtrFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 ColPtrFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.TDEST_WIDTH {0} \
 ] $ColPtrFIFO

  # Create instance: ColPtrFIFOCount, and set properties
  set ColPtrFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 ColPtrFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {9} \
   CONFIG.DOUT_WIDTH {10} \
 ] $ColPtrFIFOCount

  # Create instance: Data32Switch, and set properties
  set Data32Switch [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_switch:1.1 Data32Switch ]
  set_property -dict [ list \
   CONFIG.DECODER_REG {1} \
   CONFIG.HAS_TLAST {1} \
   CONFIG.NUM_MI {2} \
   CONFIG.NUM_SI {1} \
   CONFIG.ROUTING_MODE {0} \
 ] $Data32Switch

  # Create instance: DistVecFIFO, and set properties
  set DistVecFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 DistVecFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {1024} \
   CONFIG.FIFO_MODE {2} \
 ] $DistVecFIFO

  # Create instance: DistVecFIFOCount, and set properties
  set DistVecFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 DistVecFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {9} \
   CONFIG.DOUT_WIDTH {10} \
 ] $DistVecFIFOCount

  # Create instance: Frontend, and set properties
  set Frontend [ create_bd_cell -type ip -vlnv user.org:user:SparseFrontierFrontend:1.0 Frontend ]

  # Create instance: FrontendProfileSel, and set properties
  set FrontendProfileSel [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 FrontendProfileSel ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {2} \
   CONFIG.DOUT_WIDTH {3} \
 ] $FrontendProfileSel

  # Create instance: FrontendProfiler, and set properties
  set FrontendProfiler [ create_bd_cell -type ip -vlnv user.org:user:StateProfiler:1.0 FrontendProfiler ]

  # Create instance: FrontendStart, and set properties
  set FrontendStart [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 FrontendStart ]

  # Create instance: InputRegPlug, and set properties
  set InputRegPlug [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 InputRegPlug ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {1234567} \
   CONFIG.CONST_WIDTH {32} \
 ] $InputRegPlug

  # Create instance: LevelGenerator_0, and set properties
  set LevelGenerator_0 [ create_bd_cell -type ip -vlnv user.org:user:LevelGenerator:1.0 LevelGenerator_0 ]

  # Create instance: NFProfiler, and set properties
  set NFProfiler [ create_bd_cell -type ip -vlnv user.org:user:StateProfiler:1.0 NFProfiler ]

  # Create instance: NewDataFIFO, and set properties
  set NewDataFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 NewDataFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {1024} \
 ] $NewDataFIFO

  # Create instance: NewDataFIFOCount, and set properties
  set NewDataFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 NewDataFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {7} \
   CONFIG.DOUT_WIDTH {8} \
 ] $NewDataFIFOCount

  # Create instance: OldDataFIFO, and set properties
  set OldDataFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 OldDataFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {1024} \
 ] $OldDataFIFO

  # Create instance: OldDataFIFOCount, and set properties
  set OldDataFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 OldDataFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {7} \
   CONFIG.DOUT_WIDTH {8} \
 ] $OldDataFIFOCount

  # Create instance: RowDataFIFO, and set properties
  set RowDataFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 RowDataFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {1024} \
   CONFIG.FIFO_MODE {2} \
 ] $RowDataFIFO

  # Create instance: RowDataFIFOCount, and set properties
  set RowDataFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 RowDataFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {7} \
   CONFIG.DOUT_WIDTH {8} \
 ] $RowDataFIFOCount

  # Create instance: RowMetadataFIFO, and set properties
  set RowMetadataFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 RowMetadataFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
 ] $RowMetadataFIFO

  # Create instance: RowMetadataFIFOCount, and set properties
  set RowMetadataFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 RowMetadataFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {7} \
   CONFIG.DOUT_WIDTH {8} \
 ] $RowMetadataFIFOCount

  # Create instance: SlaveInterconnect, and set properties
  set SlaveInterconnect [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 SlaveInterconnect ]
  set_property -dict [ list \
   CONFIG.M00_HAS_REGSLICE {4} \
   CONFIG.M01_HAS_REGSLICE {4} \
   CONFIG.NUM_MI {2} \
   CONFIG.S00_HAS_REGSLICE {4} \
 ] $SlaveInterconnect

  # Create instance: SmallFIFODataCounts, and set properties
  set SmallFIFODataCounts [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 SmallFIFODataCounts ]
  set_property -dict [ list \
   CONFIG.IN0_WIDTH {8} \
   CONFIG.IN1_WIDTH {8} \
   CONFIG.IN2_WIDTH {8} \
   CONFIG.IN3_WIDTH {8} \
   CONFIG.NUM_PORTS {4} \
 ] $SmallFIFODataCounts

  # Create instance: WriteIndFIFOCount, and set properties
  set WriteIndFIFOCount [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 WriteIndFIFOCount ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {9} \
   CONFIG.DOUT_WIDTH {10} \
 ] $WriteIndFIFOCount

  # Create instance: WriteUpdateFIFO, and set properties
  set WriteUpdateFIFO [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_data_fifo:1.1 WriteUpdateFIFO ]
  set_property -dict [ list \
   CONFIG.FIFO_DEPTH {512} \
 ] $WriteUpdateFIFO

  # Create instance: blk_mem_gen_0, and set properties
  set blk_mem_gen_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:blk_mem_gen:8.4 blk_mem_gen_0 ]
  set_property -dict [ list \
   CONFIG.Assume_Synchronous_Clk {true} \
   CONFIG.Byte_Size {9} \
   CONFIG.EN_SAFETY_CKT {false} \
   CONFIG.Enable_32bit_Address {false} \
   CONFIG.Enable_A {Always_Enabled} \
   CONFIG.Enable_B {Always_Enabled} \
   CONFIG.Memory_Type {True_Dual_Port_RAM} \
   CONFIG.Operating_Mode_A {READ_FIRST} \
   CONFIG.Operating_Mode_B {READ_FIRST} \
   CONFIG.Pipeline_Stages {1} \
   CONFIG.Port_B_Clock {100} \
   CONFIG.Port_B_Enable_Rate {100} \
   CONFIG.Port_B_Write_Rate {50} \
   CONFIG.Read_Width_A {32} \
   CONFIG.Read_Width_B {32} \
   CONFIG.Register_PortA_Output_of_Memory_Core {true} \
   CONFIG.Register_PortA_Output_of_Memory_Primitives {true} \
   CONFIG.Register_PortB_Output_of_Memory_Core {true} \
   CONFIG.Register_PortB_Output_of_Memory_Primitives {true} \
   CONFIG.Use_Byte_Write_Enable {false} \
   CONFIG.Use_RSTA_Pin {false} \
   CONFIG.Write_Depth_A {1048576} \
   CONFIG.Write_Width_A {1} \
   CONFIG.Write_Width_B {1} \
   CONFIG.use_bram_block {Stand_Alone} \
 ] $blk_mem_gen_0

  # Create instance: const0, and set properties
  set const0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 const0 ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {0} \
   CONFIG.CONST_WIDTH {31} \
 ] $const0

  # Create instance: const1, and set properties
  set const1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 const1 ]

  # Create instance: internal_reset, and set properties
  set internal_reset [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 internal_reset ]

  # Create instance: internal_reset_inv, and set properties
  set internal_reset_inv [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 internal_reset_inv ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {not} \
   CONFIG.C_SIZE {1} \
   CONFIG.LOGO_FILE {data/sym_notgate.png} \
 ] $internal_reset_inv

  # Create instance: levGenStart, and set properties
  set levGenStart [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 levGenStart ]
  set_property -dict [ list \
   CONFIG.DIN_FROM {1} \
   CONFIG.DOUT_WIDTH {2} \
 ] $levGenStart

  # Create instance: reset_inv, and set properties
  set reset_inv [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 reset_inv ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {not} \
   CONFIG.C_SIZE {1} \
   CONFIG.LOGO_FILE {data/sym_notgate.png} \
 ] $reset_inv

  # Create instance: util_reduced_logic_0, and set properties
  set util_reduced_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_reduced_logic:2.0 util_reduced_logic_0 ]
  set_property -dict [ list \
   CONFIG.C_OPERATION {and} \
   CONFIG.C_SIZE {2} \
   CONFIG.LOGO_FILE {data/sym_andgate.png} \
 ] $util_reduced_logic_0

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [ list \
   CONFIG.IN1_WIDTH {31} \
 ] $xlconcat_0

  # Create interface connections
  connect_bd_intf_net -intf_net Backend_aximm32 [get_bd_intf_ports M_AXI_32] [get_bd_intf_pins Backend/aximm32]
  connect_bd_intf_net -intf_net Backend_aximm64 [get_bd_intf_ports M_AXI_64] [get_bd_intf_pins Backend/aximm64]
  connect_bd_intf_net -intf_net Backend_inpVecOutput [get_bd_intf_pins Backend/inpVecOutput] [get_bd_intf_pins OldDataFIFO/S_AXIS]
  connect_bd_intf_net -intf_net Backend_readData32 [get_bd_intf_pins Backend/readData32] [get_bd_intf_pins Data32Switch/S00_AXIS]
  connect_bd_intf_net -intf_net Backend_rowIndsData [get_bd_intf_pins Backend/rowIndsData] [get_bd_intf_pins RowDataFIFO/S_AXIS]
  connect_bd_intf_net -intf_net Backend_rowIndsMetadata [get_bd_intf_pins Backend/rowIndsMetadata] [get_bd_intf_pins RowMetadataFIFO/S_AXIS]
  connect_bd_intf_net -intf_net ColPtrFIFO_M_AXIS [get_bd_intf_pins Backend/rowStartEnd] [get_bd_intf_pins ColPtrFIFO/M_AXIS]
  connect_bd_intf_net -intf_net Data32Switch_M00_AXIS [get_bd_intf_pins Data32Switch/M00_AXIS] [get_bd_intf_pins DistVecFIFO/S_AXIS]
  connect_bd_intf_net -intf_net Data32Switch_M01_AXIS [get_bd_intf_pins ColPtrFIFO/S_AXIS] [get_bd_intf_pins Data32Switch/M01_AXIS]
  connect_bd_intf_net -intf_net DistVecFIFO_M_AXIS [get_bd_intf_pins Backend/distVecIn] [get_bd_intf_pins DistVecFIFO/M_AXIS]
  connect_bd_intf_net -intf_net Frontend_resultVectorOut [get_bd_intf_pins Frontend/resultVectorOut] [get_bd_intf_pins NewDataFIFO/S_AXIS]
  connect_bd_intf_net -intf_net LevelGenerator_0_writeIndices [get_bd_intf_pins LevelGenerator_0/writeIndices] [get_bd_intf_pins WriteUpdateFIFO/S_AXIS]
  connect_bd_intf_net -intf_net NewDataFIFO_M_AXIS [get_bd_intf_pins LevelGenerator_0/newData] [get_bd_intf_pins NewDataFIFO/M_AXIS]
  connect_bd_intf_net -intf_net OldDataFIFO_M_AXIS [get_bd_intf_pins LevelGenerator_0/oldData] [get_bd_intf_pins OldDataFIFO/M_AXIS]
  connect_bd_intf_net -intf_net S00_AXI_1 [get_bd_intf_ports S00_AXI] [get_bd_intf_pins SlaveInterconnect/S00_AXI]
  connect_bd_intf_net -intf_net SlaveInterconnect_M00_AXI [get_bd_intf_pins AXIInputRegisters_0/S00_AXI] [get_bd_intf_pins SlaveInterconnect/M00_AXI]
  connect_bd_intf_net -intf_net SlaveInterconnect_M01_AXI [get_bd_intf_pins AXIOutputRegisters_0/S00_AXI] [get_bd_intf_pins SlaveInterconnect/M01_AXI]
  connect_bd_intf_net -intf_net WriteUpdateFIFO_M_AXIS [get_bd_intf_pins Backend/distVecUpdInds] [get_bd_intf_pins WriteUpdateFIFO/M_AXIS]
  connect_bd_intf_net -intf_net axis_data_fifo_0_M_AXIS [get_bd_intf_pins Frontend/rowIndData] [get_bd_intf_pins RowDataFIFO/M_AXIS]
  connect_bd_intf_net -intf_net axis_data_fifo_1_M_AXIS [get_bd_intf_pins Frontend/rowIndMetadata] [get_bd_intf_pins RowMetadataFIFO/M_AXIS]

  # Create port connections
  connect_bd_net -net ARESETN_1 [get_bd_pins AXIInputRegisters_0/s00_axi_aresetn] [get_bd_pins AXIOutputRegisters_0/s00_axi_aresetn] [get_bd_pins SlaveInterconnect/ARESETN] [get_bd_pins SlaveInterconnect/M00_ARESETN] [get_bd_pins SlaveInterconnect/M01_ARESETN] [get_bd_pins SlaveInterconnect/S00_ARESETN] [get_bd_pins reset_inv/Res]
  connect_bd_net -net AXIOutputRegisters_0_reg0_output [get_bd_pins AXIOutputRegisters_0/reg0_output] [get_bd_pins Frontend/io_ctrl] [get_bd_pins FrontendStart/Din] [get_bd_pins levGenStart/Din]
  connect_bd_net -net AXIOutputRegisters_0_reg10_output [get_bd_pins AXIOutputRegisters_0/reg10_output] [get_bd_pins Backend/io_distVecBase]
  connect_bd_net -net AXIOutputRegisters_0_reg11_output [get_bd_pins AXIOutputRegisters_0/reg11_output] [get_bd_pins LevelGenerator_0/io_bitCount]
  connect_bd_net -net AXIOutputRegisters_0_reg12_output [get_bd_pins AXIOutputRegisters_0/reg12_output] [get_bd_pins internal_reset/Din]
  connect_bd_net -net AXIOutputRegisters_0_reg1_output [get_bd_pins AXIOutputRegisters_0/reg1_output] [get_bd_pins Frontend/io_rowCount]
  connect_bd_net -net AXIOutputRegisters_0_reg2_output [get_bd_pins AXIOutputRegisters_0/reg2_output] [get_bd_pins Frontend/io_expectedFrontierSize]
  connect_bd_net -net AXIOutputRegisters_0_reg4_output [get_bd_pins AXIOutputRegisters_0/reg4_output] [get_bd_pins Backend/io_thresholdT0]
  connect_bd_net -net AXIOutputRegisters_0_reg5_output [get_bd_pins AXIOutputRegisters_0/reg5_output] [get_bd_pins Backend/io_thresholdT1]
  connect_bd_net -net AXIOutputRegisters_0_reg6_output [get_bd_pins AXIOutputRegisters_0/reg6_output] [get_bd_pins Backend/io_rowIndBase]
  connect_bd_net -net AXIOutputRegisters_0_reg7_output [get_bd_pins AXIOutputRegisters_0/reg7_output] [get_bd_pins Backend/io_currentLevel]
  connect_bd_net -net AXIOutputRegisters_0_reg8_output [get_bd_pins AXIOutputRegisters_0/reg8_output] [get_bd_pins Backend/io_colPtrBase]
  connect_bd_net -net AXIOutputRegisters_0_reg9_output [get_bd_pins AXIOutputRegisters_0/reg9_output] [get_bd_pins Backend/io_distVecCount]
  connect_bd_net -net BACKEND_0 [get_bd_pins AXIOutputRegisters_0/reg3_output] [get_bd_pins Backend/io_ctrl] [get_bd_pins BackendStart/Din]
  connect_bd_net -net BACKEND_IOPROBE [get_bd_pins AXIInputRegisters_0/reg10_input] [get_bd_pins Backend/io_state] [get_bd_pins BackendProfiler/io_probe]
  connect_bd_net -net BackendProfileSel_Dout [get_bd_pins BackendProfileSel/Dout] [get_bd_pins BackendProfiler/io_sel] [get_bd_pins NFProfiler/io_sel]
  connect_bd_net -net BackendProfiler_io_count [get_bd_pins AXIInputRegisters_0/reg9_input] [get_bd_pins BackendProfiler/io_count]
  connect_bd_net -net BackendStart_Dout [get_bd_pins BackendProfiler/io_start] [get_bd_pins BackendStart/Dout] [get_bd_pins NFProfiler/io_start]
  connect_bd_net -net Backend_io_distVecWriteCount [get_bd_pins AXIInputRegisters_0/reg4_input] [get_bd_pins Backend/io_distVecWriteCount]
  connect_bd_net -net Backend_io_frontierSize [get_bd_pins AXIInputRegisters_0/reg2_input] [get_bd_pins Backend/io_frontierSize]
  connect_bd_net -net Backend_io_ngColCount [get_bd_pins AXIInputRegisters_0/reg5_input] [get_bd_pins Backend/io_ngColCount]
  connect_bd_net -net Backend_io_ngState [get_bd_pins Backend/io_ngState] [get_bd_pins NFProfiler/io_probe]
  connect_bd_net -net Backend_io_nzCount [get_bd_pins AXIInputRegisters_0/reg3_input] [get_bd_pins Backend/io_nzCount]
  connect_bd_net -net BigFIFODataCounts_dout [get_bd_pins AXIInputRegisters_0/reg6_input] [get_bd_pins BigFIFODataCounts/dout]
  connect_bd_net -net CLK_PROFILER [get_bd_ports clk] [get_bd_pins AXIInputRegisters_0/s00_axi_aclk] [get_bd_pins AXIOutputRegisters_0/s00_axi_aclk] [get_bd_pins Backend/clk] [get_bd_pins BackendProfiler/clk] [get_bd_pins ColPtrFIFO/s_axis_aclk] [get_bd_pins Data32Switch/aclk] [get_bd_pins DistVecFIFO/s_axis_aclk] [get_bd_pins Frontend/clk] [get_bd_pins FrontendProfiler/clk] [get_bd_pins LevelGenerator_0/clk] [get_bd_pins NFProfiler/clk] [get_bd_pins NewDataFIFO/s_axis_aclk] [get_bd_pins OldDataFIFO/s_axis_aclk] [get_bd_pins RowDataFIFO/s_axis_aclk] [get_bd_pins RowMetadataFIFO/s_axis_aclk] [get_bd_pins SlaveInterconnect/ACLK] [get_bd_pins SlaveInterconnect/M00_ACLK] [get_bd_pins SlaveInterconnect/M01_ACLK] [get_bd_pins SlaveInterconnect/S00_ACLK] [get_bd_pins WriteUpdateFIFO/s_axis_aclk] [get_bd_pins blk_mem_gen_0/clka] [get_bd_pins blk_mem_gen_0/clkb]
  connect_bd_net -net ColPtrFIFOCount_Dout [get_bd_pins BigFIFODataCounts/In1] [get_bd_pins ColPtrFIFOCount/Dout]
  connect_bd_net -net DATACOUNT_0 [get_bd_pins Backend/io_dataCountT0] [get_bd_pins DistVecFIFO/axis_data_count] [get_bd_pins DistVecFIFOCount/Din]
  connect_bd_net -net DATACOUNT_1 [get_bd_pins Backend/io_dataCountT1] [get_bd_pins ColPtrFIFO/axis_data_count] [get_bd_pins ColPtrFIFOCount/Din]
  connect_bd_net -net DistVecFIFOCount_Dout [get_bd_pins BigFIFODataCounts/In0] [get_bd_pins DistVecFIFOCount/Dout]
  connect_bd_net -net FrontendProfileSel_Dout [get_bd_pins FrontendProfileSel/Dout] [get_bd_pins FrontendProfiler/io_sel]
  connect_bd_net -net FrontendProfiler_io_count [get_bd_pins AXIInputRegisters_0/reg8_input] [get_bd_pins FrontendProfiler/io_count]
  connect_bd_net -net FrontendStart_Dout [get_bd_pins FrontendProfiler/io_start] [get_bd_pins FrontendStart/Dout]
  connect_bd_net -net Frontend_io_frontierSize [get_bd_pins AXIInputRegisters_0/reg0_input] [get_bd_pins Frontend/io_frontierSize]
  connect_bd_net -net Frontend_io_processedNZCount [get_bd_pins AXIInputRegisters_0/reg1_input] [get_bd_pins Frontend/io_processedNZCount]
  connect_bd_net -net Frontend_io_resMemPort1_addr [get_bd_pins Frontend/io_resMemPort1_addr] [get_bd_pins blk_mem_gen_0/addra]
  connect_bd_net -net Frontend_io_resMemPort1_dataWrite [get_bd_pins Frontend/io_resMemPort1_dataWrite] [get_bd_pins blk_mem_gen_0/dina]
  connect_bd_net -net Frontend_io_resMemPort1_writeEn [get_bd_pins Frontend/io_resMemPort1_writeEn] [get_bd_pins blk_mem_gen_0/wea]
  connect_bd_net -net Frontend_io_resMemPort2_addr [get_bd_pins Frontend/io_resMemPort2_addr] [get_bd_pins blk_mem_gen_0/addrb]
  connect_bd_net -net Frontend_io_resMemPort2_dataWrite [get_bd_pins Frontend/io_resMemPort2_dataWrite] [get_bd_pins blk_mem_gen_0/dinb]
  connect_bd_net -net Frontend_io_resMemPort2_writeEn [get_bd_pins Frontend/io_resMemPort2_writeEn] [get_bd_pins blk_mem_gen_0/web]
  connect_bd_net -net Frontend_io_state [get_bd_pins AXIInputRegisters_0/reg11_input] [get_bd_pins Frontend/io_state] [get_bd_pins FrontendProfiler/io_probe]
  connect_bd_net -net InputRegPlug_dout [get_bd_pins AXIInputRegisters_0/reg15_input] [get_bd_pins InputRegPlug/dout]
  connect_bd_net -net LevelGenerator_0_io_finished [get_bd_pins LevelGenerator_0/io_finished] [get_bd_pins xlconcat_0/In0]
  connect_bd_net -net LevelGenerator_0_io_writeCount [get_bd_pins AXIInputRegisters_0/reg12_input] [get_bd_pins LevelGenerator_0/io_writeCount]
  connect_bd_net -net NFProfiler_io_count [get_bd_pins AXIInputRegisters_0/reg14_input] [get_bd_pins NFProfiler/io_count]
  connect_bd_net -net Net [get_bd_pins ColPtrFIFO/s_axis_aresetn] [get_bd_pins Data32Switch/aresetn] [get_bd_pins DistVecFIFO/s_axis_aresetn] [get_bd_pins NewDataFIFO/s_axis_aresetn] [get_bd_pins OldDataFIFO/s_axis_aresetn] [get_bd_pins RowDataFIFO/s_axis_aresetn] [get_bd_pins RowMetadataFIFO/s_axis_aresetn] [get_bd_pins WriteUpdateFIFO/s_axis_aresetn] [get_bd_pins internal_reset_inv/Res]
  connect_bd_net -net NewDataFIFOCount_Dout [get_bd_pins NewDataFIFOCount/Dout] [get_bd_pins SmallFIFODataCounts/In3]
  connect_bd_net -net NewDataFIFO_axis_data_count [get_bd_pins NewDataFIFO/axis_data_count] [get_bd_pins NewDataFIFOCount/Din]
  connect_bd_net -net OldDataFIFOCount_Dout [get_bd_pins OldDataFIFOCount/Dout] [get_bd_pins SmallFIFODataCounts/In2]
  connect_bd_net -net OldDataFIFO_axis_data_count [get_bd_pins OldDataFIFO/axis_data_count] [get_bd_pins OldDataFIFOCount/Din]
  connect_bd_net -net PROFILESEL_0 [get_bd_pins AXIOutputRegisters_0/reg13_output] [get_bd_pins BackendProfileSel/Din] [get_bd_pins FrontendProfileSel/Din]
  connect_bd_net -net RESET_PROFILER [get_bd_pins Backend/reset] [get_bd_pins BackendProfiler/reset] [get_bd_pins Frontend/reset] [get_bd_pins FrontendProfiler/reset] [get_bd_pins LevelGenerator_0/reset] [get_bd_pins NFProfiler/reset] [get_bd_pins internal_reset/Dout] [get_bd_pins internal_reset_inv/Op1]
  connect_bd_net -net RowDataFIFOCount_Dout [get_bd_pins RowDataFIFOCount/Dout] [get_bd_pins SmallFIFODataCounts/In0]
  connect_bd_net -net RowDataFIFO_axis_data_count [get_bd_pins RowDataFIFO/axis_data_count] [get_bd_pins RowDataFIFOCount/Din]
  connect_bd_net -net RowMetadataFIFOCount_Dout [get_bd_pins RowMetadataFIFOCount/Dout] [get_bd_pins SmallFIFODataCounts/In1]
  connect_bd_net -net RowMetadataFIFO_axis_data_count [get_bd_pins RowMetadataFIFO/axis_data_count] [get_bd_pins RowMetadataFIFOCount/Din]
  connect_bd_net -net SmallFIFODataCounts_dout [get_bd_pins AXIInputRegisters_0/reg7_input] [get_bd_pins SmallFIFODataCounts/dout]
  connect_bd_net -net WriteIndFIFOCount_Dout [get_bd_pins BigFIFODataCounts/In2] [get_bd_pins WriteIndFIFOCount/Dout]
  connect_bd_net -net WriteUpdateFIFO_axis_data_count [get_bd_pins WriteIndFIFOCount/Din] [get_bd_pins WriteUpdateFIFO/axis_data_count]
  connect_bd_net -net blk_mem_gen_0_douta [get_bd_pins Frontend/io_resMemPort1_dataRead] [get_bd_pins blk_mem_gen_0/douta]
  connect_bd_net -net blk_mem_gen_0_doutb [get_bd_pins Frontend/io_resMemPort2_dataRead] [get_bd_pins blk_mem_gen_0/doutb]
  connect_bd_net -net const0_dout [get_bd_pins const0/dout] [get_bd_pins xlconcat_0/In1]
  connect_bd_net -net const1_dout [get_bd_pins LevelGenerator_0/newDataCopy_TREADY] [get_bd_pins const1/dout]
  connect_bd_net -net levGenStart_Dout [get_bd_pins levGenStart/Dout] [get_bd_pins util_reduced_logic_0/Op1]
  connect_bd_net -net reset_1 [get_bd_ports reset] [get_bd_pins reset_inv/Op1]
  connect_bd_net -net util_reduced_logic_0_Res [get_bd_pins LevelGenerator_0/io_start] [get_bd_pins util_reduced_logic_0/Res]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins AXIInputRegisters_0/reg13_input] [get_bd_pins xlconcat_0/dout]

  # Create address segments
  variable M_AXI_GP0_BASEADDR
  set M_AXI_GP0_BASEADDR $::M_AXI_32_BASE_ADDR																																																									   
  create_bd_addr_seg -range 0x00010000 -offset $M_AXI_GP0_BASEADDR [get_bd_addr_spaces Backend/aximm32] [get_bd_addr_segs M_AXI_32/Reg] SEG_M_AXI_32_Reg
  create_bd_addr_seg -range 0x00010000 -offset $M_AXI_GP0_BASEADDR [get_bd_addr_spaces Backend/aximm64] [get_bd_addr_segs M_AXI_64/Reg] SEG_M_AXI_64_Reg
  create_bd_addr_seg -range 0x00001000 -offset $M_AXI_32_BASE_ADDR [get_bd_addr_spaces S00_AXI] [get_bd_addr_segs AXIInputRegisters_0/S00_AXI/S00_AXI_reg] SEG_AXIInputRegisters_0_S00_AXI_reg
  create_bd_addr_seg -range 0x00001000 -offset $AXI_OUTPUT_BASEADDR [get_bd_addr_spaces S00_AXI] [get_bd_addr_segs AXIOutputRegisters_0/S00_AXI/S00_AXI_reg] SEG_AXIOutputRegisters_0_S00_AXI_reg


  # Restore current instance
  current_bd_instance $oldCurInst
  validate_bd_design
  regenerate_bd_layout
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


