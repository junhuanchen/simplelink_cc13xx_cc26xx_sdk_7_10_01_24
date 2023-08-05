# Radio Co-Processor Example Application

## Table of Contents

* [SysConfig Notice](#sysconfig-notice)
* [Introduction](#intro)
* [Hardware Prerequisites](#hardware-prereqs)
* [Software Prerequisites](#software-prereqs)
* [Functional Description](#functional-desc)
  * [Software Overview](#software-overview)
    * [Application Files](#application)
    * [Example Application](#example-application)
* [Configuration With SysConfig](#sysconfig)
* [Usage](#usage)
  * [Buttons](#usage-buttons)
  * [Display](#usage-display)

# <a name="intro"></a> Introduction

This document discusses how to use the Radio Co-Processor (RCP) example
application.

The RCP example is intended to be used with a host processor connected through
UART or SPI. This example is setup to connect with the UART interface over the
XDS110 USB-to-UART. The RCP uses the Spinel protocol to communicate to the
host. The RCP can be used with the OpenThread border router packages from
OpenThread. This example requires the higher-level protocol features to be run
on the host processor.

# <a name="hardware-prereqs"></a> Hardware Prerequisites

- 2 x CC13X2 / CC26X2 Wireless MCU LaunchPads

- 1 x Linux computer


# <a name="software-prereqs"></a> Software Prerequisites

- Code Composer Studio (CCS) v10.0 or higher


# <a name="functional-desc"></a> Functional Description


## <a name="software-overview"></a> Software Overview

This section describes software components and the corresponding source file.


### <a name="application"></a> Application Files

- `main.c`: The main entry point for the example. Creates and starts the tasks
  for operating the OpenThread stack and RCP example.

- `rcp.c`: Instantiation of Radio Co-Processor object and heartbeat LED loop.

- `otstack.c`: OpenThread stack instantiation and processing.

- `task_config.h`: Defines RTOS task priorities and call stack sizes.

- `tiop_config.[ch]`: Contains OpenThread stack configurations. If using a
  SysConfig-enabled project (see the Configuration with SysConfig section
  below), these files are generated and configured through the SysConfig GUI.
  If using a non-SysConfig project, the files are a part of the project and
  parameters can be directly modified.


### <a name="example-application"></a> Example Application

This application provides a simplified MAC interface over Spinel for an
OpenThread application running on a Linux based host processor.

A full example of the RCP working with a host processor can be found in the
[Border Router Repository][br-gh]. This will create a border router on the host
processor that allows off-mesh commissioning. Information on building the
border router can be found on [openthread.io][br-install].

[br-gh]: https://github.com/openthread/borderrouter
[br-install]: https://openthread.io/guides/border_router/beaglebone_black
[wpantund-gh]: https://github.com/openthread/wpantund
[wpantund-install]: https://github.com/openthread/wpantund


# <a name="sysconfig"></a> Configuration With SysConfig

SysConfig is a GUI configuration tool that allows for TI driver and stack
configurations. In order to configure projects using SysConfig, use the
SysConfig-enabled version of the Thread examples located in
`<SDK_ROOT>/examples`

To configure using SysConfig, import the SysConfig-enabled project into CCS.
Double click the `*.syscfg` file from the CCS project explorer, where `*` is
the name of the example project. The SysConfig GUI window will appear, where
Thread stack and TI driver configurations can be adjusted. These settings will
be reflected in the generated files `tiop_config.[ch]`.

The example project comes with working default settings for SysConfig. It is
not recommended to change the default driver settings, as any changes may
impact the functionality of the example. The Thread stack settings may be
changed as required for your use case.

One important note about TI-OpenThread SysConfig is how SysConfig settings and
non-volatile storage settings are applied. If the LaunchPad non-volatile holds
a valid Thread dataset, SysConfig settings will not be applied on boot.
SysConfig settings are only applied when non-volatile storage does not hold a
valid Thread dataset. To guarantee SysConfig settings are applied, perform a
factory reset of the non-volatile storage, as described below.


# <a name="usage"></a> Usage

This section describes how to set up and run the RCP Example Application. It is
assumed that you have installed the OpenThread border router on the host Linux
machine.

Follow the guides on openthread.io for further information on setting up an
OpenThread Border Router.


## <a name="usage-buttons"></a> Buttons

- `BTN-2` at boot: A factory reset of the non-volatile storage is
  performed.  This must be pressed at the start of the `OtStack_task` function.

## <a name="usage-display"></a> Display

There is no display for the RCP example application.

