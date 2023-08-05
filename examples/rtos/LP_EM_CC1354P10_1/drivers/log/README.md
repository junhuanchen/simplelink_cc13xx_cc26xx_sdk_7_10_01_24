
## Log Example

This example shows how to instrument your source code using `Log`.
Additionally it shows how to configure route log sites to a logger transport
instance.

## Resources & Jumper Settings

> If you're using an IDE (such as CCS or IAR), please refer to Board.html in
your project directory for resources used and board-specific jumper settings.
Otherwise, you can find Board.html in the directory
&lt;SDK_INSTALL_DIR&gt;/source/ti/boards/&lt;BOARD&gt;.

If using CC32xx, then the device must be debugged in SWD mode and the SOP
jumper must be placed in position 0 in order to send ITM messages
on the SWO pin.

If using CC13XX/26XX the SWO jumper must be connected on the LaunchPad.

* NOTE: For CC13X4/26X4 boards, ITM will only output data while a debugger is
connected. For these devices, it is necessary to launch a debug session instead
of simply flashing the target and running it. While remaining in the debug session, the device
can be reset to output the reset-frame over ITM using the debugger. In CCS this
can done from the menu `Run -> Reset`

## Definitions

The following terms are used throughout the Readme.

| Term                            | Definition                                                                                                                                                                                                                                                                                                                     |
|---------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `LogModule`                     | A parameter passed to Log APIs to indicate which software module the log statement originated from. Modules also control the routing of logs to sinks.                                                                                                                                                                         |
| `LogLevel`                      | The severity or importance of a given log statement.                                                                                                                                                                                                    |
| `Sink`                          | Also simply called a logger. This is a transport specific logger implementation. <br> The Logging framework is flexible such that multiple sinks may exist in a single firmware image.                                                                                                                                         |
| `CallSite`                      | A specific invocation of a Log API in a given file or program.                                                                                                                                                                                                                                                                 |
| `Record`                        | The binary representation of a log when it is stored or transported by a given sink. The log record format varys slightly with each sink depending on their implementation and needs. However, they all convey the same information.                                                                                           |
| Link Time Optimization (LTO)    | A feature of some toolchains that can significantly reduce the code overhead of the log statements through a process called dead code elimination. In order to maximize the benefits of this, all static libraries and application files should have LTO enabled.                                                              |


###  Highlights

  * Exercises the Logging API showing common use cases.
  * Uses two separate LogModules.
     - `LogModule_App1` uses the default sink LogSinkBuf which routes logs to memory
     - `LogModule_App2` is a second module that routes logs to ITM on devices which supports it
  * Exercises the ITM and buffer based loggers (`LogSinkBuf`, `LogSinkITM`).
  * Application runs in a task which wakes up every 5 seconds.

###  Beta Disclaimer

The logging ecosystem and this example are to be considered beta quality.
They are not recommended for use in production code by TI.
APIs and behaviour will change in future releases.
Please report issues or feedback to [__E2E__][e2e].

TI is seeking feedback in the following areas:

 * Presentation/configuration of logging in SysConfig.
 * Log API

### Overview

The example uses LTO to control inclusion of log statements in the built binary. There are two log
modules used.

The routing of the log data is controlled by the relevant LogModule instance in
SysConfig. This routing is controlled at the module level. That is,
all log data from a given module goes to the same log sink.

The big picture:

```
file.c -->|[x]--> LogSinkBuf  --> memory, ROV
          |[ ]--> LogSinkITM  --> ITM, Wireshark
            ^
            |
LogModule --+
```

Visualization of logs depends on their transport. This is discussed in the
following section.

## Log Visualization

Each log module is routed to a different log sink.
Due to the differing nature of the transport mechanisms used by the back end
delegates, they are visualized using different methods. The table below shows
the tooling used for visualizing the different types of logs.

| Logger      | Visualization tool            |
|-------------|-------------------------------|
| `LogSinkBuf` | Runtime Object View (ROV) 2   |
| `LogSinkITM` | Wireshark + TI Python Backend |

The log statements can be viewed independently. It is not required to have
both host side tools running in order for the example to run.

## Example Usage

This demo illustrates a working example of logging. Note that some log sinks require special hardware initialization.
In this example, both LogSinkITM and LogSinkBuf are used, but only LogSinkITM requires initialization:
```c
LogSinkITM_init();
```
Please refer to the documentation of the particular log sink for more information on usage.


### Import and Build the Example

 1. Import the project into your workspace.

 1. Build the project.

### Load and Run the Program

This program uses ROV to display program output. You may interact with
the program using memory flags controlled through the Expressions view.

 1. Follow the Quick Start Guide instructions in the readme in `<SDK_INSTALL_DIR>/tools/log/tiutils`
 1. Load the program.

 1. To view LogSinkBuf statements: Launch ROV.
    ```
    Tools -> Runtime Object View
    ```

    Open the ROV `LogSinkBuf` view

    ```
    Tools > Runtime Object View
    Connect
    LogSinkBuf
    LogSinkBuf > Records
    ```

    Enable continuous refresh to see the output as it is generated.
    The default refresh rate is 1 second.

 1. To view LogSinkITM statements: Launch Wireshark.

    Follow the steps in the "Extracting some Logs" section of the readme in
    `<SDK_INSTALL_DIR>/tools/log/tiutils`

 1. Run the program.

    In ROV, you will see the initial start up message, followed by a count
    update every 5 seconds.

    ```
    count=1
    count=2
    count=3
    ```

    In Wireshark, you will see the initial start up message (Hello world), and
    messages whenever the application's semaphore is posted

    ```
    log_clkFxn: post semaphore
    ...
    ```


Note: LogSinkBuf requires ROV2 which is not available in IAR. Thus, there is
no proper visualizer for these messages besides inspecting their records in
memory. The ITM transport is supported across all IDEs/toolchains.


## Conditional Log Inclusion

Log invocations are conditionally included in the final program based on the
settings of the corresponding log module, if link-time optimization is enabled.
If the log module is disabled, or the log-level for the particular invocation is insufficient,
the linker will perform dead-code elimination, and optimize the call away.

It is therefore recommended to build with link time optimization if the toolchain
supports it.

## Source Code Instrumentation

To add instrumentation to your source code, requires three steps:

  1. Include Log.h
  2. Define a log module name
  3. Add an instrumentation call site

In log.c, you will see the following code which prints a greeting:

```c
#include <ti/log/Log.h>

Log_printf(LogModule_App1, Log_DEBUG, "Hello World!");
```

The above code will implicitly declare a log module called LogModule_App1.
This means that a logModule called LogModule_App1 must be defined, most easily
by SysConfig. The log data associated with this log module will be routed to the logger
instance specified by LogModule_App1.

## Adding Modules

All log statements in the above example use either LogModule_App1 or LogModule_App2.
Log modules are useful for grouping and sorting log statements that share configrations
such as severity levels and sinks. In order to create a new module follow
the steps below:

  1. Define a module name
  1. Create a Log module in SysConfig with the given name
  1. Configure the Log module to use a desired sink, and set log levels

## SysConfig

Open the Logging category. You will find the following modules:

  * Log Modules - a list of all defined log modules, along with their respective configurations
  * Log Sinks - this lists all available sinks that logs can be routed to
  * LogSinkBuf - all instances of LogSinkBuf. Each instances is a seperate memory area that logs can be written to. Each sink can be configured separately.
  * LogSinkITM - due to hardware limitations, there is only one available ITM sink. However, several different modules may use it as a sink.

[e2e]: https://e2e.ti.com/
