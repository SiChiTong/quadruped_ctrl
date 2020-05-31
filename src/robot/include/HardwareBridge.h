/*!
 * @file HardwareBridge.h
 * @brief Interface between robot code and robot hardware
 *
 * This class initializes the hardware of both robots and allows the robot
 * controller to access it
 */

#ifndef PROJECT_HARDWAREBRIDGE_H
#define PROJECT_HARDWAREBRIDGE_H

// #ifdef linux 

#define MAX_STACK_SIZE 16384  // 16KB  of stack
#define TASK_PRIORITY 49      // linux priority, this is not the nice value

#include <string>
//delete lcm
// #include <lcm-cpp.hpp>
// #include "control_parameter_request_lcmt.hpp"
// #include "control_parameter_respones_lcmt.hpp"
// #include "microstrain_lcmt.hpp"
// #include "ecat_command_t.hpp"
// #include "ecat_data_t.hpp"
// #include "gamepad_lcmt.hpp"
// #include <lord_imu/LordImu.h>

#include "RobotRunner.h"
#include "Utilities/PeriodicTask.h"





/*!
 * Interface between robot and hardware
 */
class HardwareBridge {
 public:
  HardwareBridge(RobotController* robot_ctrl)
      : statusTask(&taskManager, 0.5f)
      //delete lcm
        // _interfaceLCM(getLcmUrl(255)),
        // _visualizationLCM(getLcmUrl(255)) {
  {
    _controller = robot_ctrl;
    _userControlParameters = robot_ctrl->getUserControlParameters();
  }
  void initError(const char* reason, bool printErrno = false);
  ~HardwareBridge() { delete _robotRunner; }
  //delete lcm
//   void handleGamepadLCM(const lcm::ReceiveBuffer* rbuf, const std::string& chan,
//                         const gamepad_lcmt* msg);

//   void handleInterfaceLCM();
//   void handleControlParameter(const lcm::ReceiveBuffer* rbuf,
//                               const std::string& chan,
//                               const control_parameter_request_lcmt* msg);

  void publishVisualizationLCM();
  void run_sbus();

 protected:
  PeriodicTaskManager taskManager;
  PrintTaskStatus statusTask;
  //delete gamepad
  // GamepadCommand _gamepadCommand;
  //delete lcm
  //   CheetahVisualization _mainCheetahVisualization;
//   lcm::LCM _interfaceLCM;
//   lcm::LCM _visualizationLCM;
//   control_parameter_respones_lcmt _parameter_response_lcmt;
//   SpiData _spiData;
//   SpiCommand _spiCommand;
//   TiBoardCommand _tiBoardCommand[4];
//   TiBoardData _tiBoardData[4];
//   VisualizationData _visualizationData;

  bool _firstRun = true;
  RobotRunner* _robotRunner = nullptr;
  RobotControlParameters _robotParams;
  u64 _iterations = 0;
  //delete lcm
//   std::thread _interfaceLcmThread;
//   volatile bool _interfaceLcmQuit = false;
  RobotController* _controller = nullptr;
  ControlParameters* _userControlParameters = nullptr;

  int _port;
};

/*!
 * Interface between robot and hardware specialized for Mini Cheetah
 */
class MiniCheetahHardwareBridge : public HardwareBridge {
 public:
  MiniCheetahHardwareBridge(RobotController* rc, bool load_parameters_from_file);
  void runSpi();
  void initHardware();
  void run();
  //delete imu
//   void runMicrostrain();
//   void logMicrostrain();
  void abort(const std::string& reason);
  void abort(const char* reason);

 private:
  VectorNavData _vectorNavData;
  //delete lcm
//   lcm::LCM _spiLcm;
//   lcm::LCM _microstrainLcm;
//   microstrain_lcmt _microstrainData;
//   std::thread _microstrainThread;
//   LordImu _microstrainImu;
//   bool _microstrainInit = false;
  bool _load_parameters_from_file;
};

// #endif // END of #ifdef linux
#endif  // PROJECT_HARDWAREBRIDGE_H
