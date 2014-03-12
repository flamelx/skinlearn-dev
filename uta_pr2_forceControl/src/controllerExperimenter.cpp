/*
 * controllerExperimenter.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: isura
 */

#include <ros/ros.h>
#include <uta_pr2_forceControl/controllerFullData.h>
#include <uta_pr2_forceControl/controllerParam.h>
#include <uta_pr2_forceControl/controllerParamUpdate.h>
#include <std_srvs/Empty.h>

#include <yaml-cpp/yaml.h>

#include <iostream>
#include <fstream>
using namespace std;

class controllerExperimenter
{
  ros::NodeHandle  node;

  ros::ServiceClient capture_client;
  ros::ServiceClient paramUpdate_client;

  ros::Subscriber subControllerFullData;

  int dataCounter;
  int dataLength;
  uint trialNumber;

  bool dataCollectedFlag;

  ofstream dataFile;

  string experimentParameterFile;
  std::vector<std::string> trialNames;
  std::vector<uta_pr2_forceControl::controllerParam> trialData;

  YAML::Parser parser;
  YAML::Node doc;

public:

  controllerExperimenter()
  {
    // FIXME the pr2_neuroadptController/ part should be generalized
    paramUpdate_client = node.serviceClient<uta_pr2_forceControl::controllerParamUpdate>("pr2_neuroadptController/paramUpdate");
    capture_client     = node.serviceClient<std_srvs::Empty>("pr2_neuroadptController/capture");

    subControllerFullData = node.subscribe("pr2_neuroadptController/controllerFullData", 10000, &controllerExperimenter::fullDataCallback, this );

    dataCounter = 0;
    dataLength  = 100000;

    dataCollectedFlag = true;

    trialNumber = 1;

    std::string para_experimentParameterFile   = "/experimentParameterFile";
    if (!node.getParam(para_experimentParameterFile, experimentParameterFile))
    { ROS_ERROR("Value not loaded from parameter: %s !)", para_experimentParameterFile.c_str()); }

    std::ifstream fin;
    fin.open(experimentParameterFile.c_str());

    if (fin)
    {
      ROS_INFO("Experimental Parameter Load Success!");
    }
    else
    {
      ROS_ERROR("Experimental Parameter Load Fail!");
    }

    parser.Load(fin);
    parser.GetNextDocument(doc);

    trialData.resize(doc.size());

    std::string names;
    for (unsigned i = 0; i < doc.size(); i++)
    {
      doc[i]["trialName"] >> names;
      trialNames.push_back(names);
      std::cout << "trialName: " << names << "---\n";

      // TODO finish this
      trialData[i].inParams         = 35   ;
      trialData[i].outParams        = 7    ;
      trialData[i].hiddenNodes      = 10   ;
      trialData[i].errorParams      = 7    ;

      trialData[i].kappa            = 0.07 ;
      trialData[i].Kv               = 5    ;
      trialData[i].lambda           = 20   ;
      trialData[i].Kz               = 0.001;
      trialData[i].Zb               = 100  ;
      trialData[i].feedForwardForce = 0    ;
      trialData[i].nn_ON            = 0    ;
      trialData[i].F                = 100  ;
      trialData[i].G                = 100  ;

    }

    fin.close();

  }

  ~controllerExperimenter() { }

  void fullDataCallback(const uta_pr2_forceControl::controllerFullData::ConstPtr& msg)
  {
    dataCounter += 1;

    ROS_ERROR_STREAM("Writing " << dataCounter );
    dataFile << "Writing this to a file.\n";

    if( dataCounter >= dataLength )
    {
      dataCollectedFlag = true;
      dataCounter = 0;
      dataFile.close();
      ROS_ERROR_STREAM("Trial " << trialNumber << " : " << trialNames[trialNumber-1] << " complete!");
    }

  }

  void go()
  {

    ROS_ERROR_STREAM("# Starting Experiment #");

    while( ros::ok() && !(trialNumber > trialNames.size()) )
    {
        // Only do this if data is not being collected
        if( dataCollectedFlag )
        {
          ROS_ERROR_STREAM("Starting Trial: " << trialNames[trialNumber-1]);
          string trialName = trialNames[trialNumber-1];
          dataFile.open(trialName.c_str());

          uta_pr2_forceControl::controllerParamUpdate controllerParamServ;
          controllerParamServ.request.msg = trialData[trialNumber-1];

          paramUpdate_client.call(controllerParamServ);

          if( controllerParamServ.response.success )
          {

            ROS_ERROR_STREAM("RESPONSE");

            dataCollectedFlag = false;
            std_srvs::Empty captureSrv;
            capture_client.call(captureSrv);
          }else
          {
            ROS_ERROR_STREAM("NO RESPONSE");
          }

          usleep(1000);

          trialNumber += 1;
        }

    }
  }

};

int
main( int argc, char** argv )
{
    // Initialize ROS
    ros::init (argc, argv, "controllerExperimenter");
    ros::NodeHandle nh;

    ROS_ERROR_STREAM("### DEBUG ###");
    controllerExperimenter controllerExperimenterObj;

    controllerExperimenterObj.go();
}
