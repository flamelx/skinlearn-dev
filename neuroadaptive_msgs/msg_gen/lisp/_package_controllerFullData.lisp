(cl:in-package neuroadaptive_msgs-msg)
(cl:export '(DT-VAL
          DT
          FORCE_X-VAL
          FORCE_X
          FORCE_Y-VAL
          FORCE_Y
          FORCE_Z-VAL
          FORCE_Z
          TORQUE_X-VAL
          TORQUE_X
          TORQUE_Y-VAL
          TORQUE_Y
          TORQUE_Z-VAL
          TORQUE_Z
          ACC_X-VAL
          ACC_X
          ACC_Y-VAL
          ACC_Y
          ACC_Z-VAL
          ACC_Z
          R_EFF_X-VAL
          R_EFF_X
          R_EFF_Y-VAL
          R_EFF_Y
          R_EFF_Z-VAL
          R_EFF_Z
          R_TRQ_X-VAL
          R_TRQ_X
          R_TRQ_Y-VAL
          R_TRQ_Y
          R_TRQ_Z-VAL
          R_TRQ_Z
          REFERENCE_EFF_J0-VAL
          REFERENCE_EFF_J0
          REFERENCE_EFF_J1-VAL
          REFERENCE_EFF_J1
          REFERENCE_EFF_J2-VAL
          REFERENCE_EFF_J2
          REFERENCE_EFF_J3-VAL
          REFERENCE_EFF_J3
          REFERENCE_EFF_J4-VAL
          REFERENCE_EFF_J4
          REFERENCE_EFF_J5-VAL
          REFERENCE_EFF_J5
          REFERENCE_EFF_J6-VAL
          REFERENCE_EFF_J6
          TASKREF_X-VAL
          TASKREF_X
          TASKREF_Y-VAL
          TASKREF_Y
          TASKREF_Z-VAL
          TASKREF_Z
          TASKREF_PHI-VAL
          TASKREF_PHI
          TASKREF_THETA-VAL
          TASKREF_THETA
          TASKREF_PSI-VAL
          TASKREF_PSI
          TASKREFMODEL_X-VAL
          TASKREFMODEL_X
          TASKREFMODEL_Y-VAL
          TASKREFMODEL_Y
          TASKREFMODEL_Z-VAL
          TASKREFMODEL_Z
          TASKREFMODEL_PHI-VAL
          TASKREFMODEL_PHI
          TASKREFMODEL_THETA-VAL
          TASKREFMODEL_THETA
          TASKREFMODEL_PSI-VAL
          TASKREFMODEL_PSI
          M_CARTPOS_X-VAL
          M_CARTPOS_X
          M_CARTPOS_Y-VAL
          M_CARTPOS_Y
          M_CARTPOS_Z-VAL
          M_CARTPOS_Z
          M_CARTPOS_QX-VAL
          M_CARTPOS_QX
          M_CARTPOS_QY-VAL
          M_CARTPOS_QY
          M_CARTPOS_QZ-VAL
          M_CARTPOS_QZ
          M_CARTPOS_QW-VAL
          M_CARTPOS_QW
          M_POS_X-VAL
          M_POS_X
          M_POS_Y-VAL
          M_POS_Y
          M_POS_Z-VAL
          M_POS_Z
          M_VEL_X-VAL
          M_VEL_X
          M_VEL_Y-VAL
          M_VEL_Y
          M_VEL_Z-VAL
          M_VEL_Z
          M_ACC_X-VAL
          M_ACC_X
          M_ACC_Y-VAL
          M_ACC_Y
          M_ACC_Z-VAL
          M_ACC_Z
          M_POS_J0-VAL
          M_POS_J0
          M_POS_J1-VAL
          M_POS_J1
          M_POS_J2-VAL
          M_POS_J2
          M_POS_J3-VAL
          M_POS_J3
          M_POS_J4-VAL
          M_POS_J4
          M_POS_J5-VAL
          M_POS_J5
          M_POS_J6-VAL
          M_POS_J6
          M_VEL_J0-VAL
          M_VEL_J0
          M_VEL_J1-VAL
          M_VEL_J1
          M_VEL_J2-VAL
          M_VEL_J2
          M_VEL_J3-VAL
          M_VEL_J3
          M_VEL_J4-VAL
          M_VEL_J4
          M_VEL_J5-VAL
          M_VEL_J5
          M_VEL_J6-VAL
          M_VEL_J6
          M_ACC_J0-VAL
          M_ACC_J0
          M_ACC_J1-VAL
          M_ACC_J1
          M_ACC_J2-VAL
          M_ACC_J2
          M_ACC_J3-VAL
          M_ACC_J3
          M_ACC_J4-VAL
          M_ACC_J4
          M_ACC_J5-VAL
          M_ACC_J5
          M_ACC_J6-VAL
          M_ACC_J6
          M_EFF_J0-VAL
          M_EFF_J0
          M_EFF_J1-VAL
          M_EFF_J1
          M_EFF_J2-VAL
          M_EFF_J2
          M_EFF_J3-VAL
          M_EFF_J3
          M_EFF_J4-VAL
          M_EFF_J4
          M_EFF_J5-VAL
          M_EFF_J5
          M_EFF_J6-VAL
          M_EFF_J6
          CONTROL_EFF_J0-VAL
          CONTROL_EFF_J0
          CONTROL_EFF_J1-VAL
          CONTROL_EFF_J1
          CONTROL_EFF_J2-VAL
          CONTROL_EFF_J2
          CONTROL_EFF_J3-VAL
          CONTROL_EFF_J3
          CONTROL_EFF_J4-VAL
          CONTROL_EFF_J4
          CONTROL_EFF_J5-VAL
          CONTROL_EFF_J5
          CONTROL_EFF_J6-VAL
          CONTROL_EFF_J6
          R_CARTPOS_X-VAL
          R_CARTPOS_X
          R_CARTPOS_Y-VAL
          R_CARTPOS_Y
          R_CARTPOS_Z-VAL
          R_CARTPOS_Z
          R_CARTPOS_QX-VAL
          R_CARTPOS_QX
          R_CARTPOS_QY-VAL
          R_CARTPOS_QY
          R_CARTPOS_QZ-VAL
          R_CARTPOS_QZ
          R_CARTPOS_QW-VAL
          R_CARTPOS_QW
          R_POS_J0-VAL
          R_POS_J0
          R_POS_J1-VAL
          R_POS_J1
          R_POS_J2-VAL
          R_POS_J2
          R_POS_J3-VAL
          R_POS_J3
          R_POS_J4-VAL
          R_POS_J4
          R_POS_J5-VAL
          R_POS_J5
          R_POS_J6-VAL
          R_POS_J6
          R_VEL_J0-VAL
          R_VEL_J0
          R_VEL_J1-VAL
          R_VEL_J1
          R_VEL_J2-VAL
          R_VEL_J2
          R_VEL_J3-VAL
          R_VEL_J3
          R_VEL_J4-VAL
          R_VEL_J4
          R_VEL_J5-VAL
          R_VEL_J5
          R_VEL_J6-VAL
          R_VEL_J6
          R_ACC_J0-VAL
          R_ACC_J0
          R_ACC_J1-VAL
          R_ACC_J1
          R_ACC_J2-VAL
          R_ACC_J2
          R_ACC_J3-VAL
          R_ACC_J3
          R_ACC_J4-VAL
          R_ACC_J4
          R_ACC_J5-VAL
          R_ACC_J5
          R_ACC_J6-VAL
          R_ACC_J6
          R_EFF_J0-VAL
          R_EFF_J0
          R_EFF_J1-VAL
          R_EFF_J1
          R_EFF_J2-VAL
          R_EFF_J2
          R_EFF_J3-VAL
          R_EFF_J3
          R_EFF_J4-VAL
          R_EFF_J4
          R_EFF_J5-VAL
          R_EFF_J5
          R_EFF_J6-VAL
          R_EFF_J6
          L_LIMIT_0-VAL
          L_LIMIT_0
          L_LIMIT_1-VAL
          L_LIMIT_1
          L_LIMIT_2-VAL
          L_LIMIT_2
          L_LIMIT_3-VAL
          L_LIMIT_3
          L_LIMIT_4-VAL
          L_LIMIT_4
          L_LIMIT_5-VAL
          L_LIMIT_5
          L_LIMIT_6-VAL
          L_LIMIT_6
          U_LIMIT_0-VAL
          U_LIMIT_0
          U_LIMIT_1-VAL
          U_LIMIT_1
          U_LIMIT_2-VAL
          U_LIMIT_2
          U_LIMIT_3-VAL
          U_LIMIT_3
          U_LIMIT_4-VAL
          U_LIMIT_4
          U_LIMIT_5-VAL
          U_LIMIT_5
          U_LIMIT_6-VAL
          U_LIMIT_6
          KAPPA-VAL
          KAPPA
          KV-VAL
          KV
          LAMBDA-VAL
          LAMBDA
          KZ-VAL
          KZ
          ZB-VAL
          ZB
          F-VAL
          F
          G-VAL
          G
          INPARAMS-VAL
          INPARAMS
          OUTPARAMS-VAL
          OUTPARAMS
          HIDDENNODES-VAL
          HIDDENNODES
          ERRORPARAMS-VAL
          ERRORPARAMS
          FEEDFORWARDFORCE-VAL
          FEEDFORWARDFORCE
          NN_ON-VAL
          NN_ON
          CARTPOS_KP_X-VAL
          CARTPOS_KP_X
          CARTPOS_KP_Y-VAL
          CARTPOS_KP_Y
          CARTPOS_KP_Z-VAL
          CARTPOS_KP_Z
          CARTPOS_KD_X-VAL
          CARTPOS_KD_X
          CARTPOS_KD_Y-VAL
          CARTPOS_KD_Y
          CARTPOS_KD_Z-VAL
          CARTPOS_KD_Z
          CARTROT_KP_X-VAL
          CARTROT_KP_X
          CARTROT_KP_Y-VAL
          CARTROT_KP_Y
          CARTROT_KP_Z-VAL
          CARTROT_KP_Z
          CARTROT_KD_X-VAL
          CARTROT_KD_X
          CARTROT_KD_Y-VAL
          CARTROT_KD_Y
          CARTROT_KD_Z-VAL
          CARTROT_KD_Z
          USECURRENTCARTPOSE-VAL
          USECURRENTCARTPOSE
          USENULLSPACEPOSE-VAL
          USENULLSPACEPOSE
          CARTINIX-VAL
          CARTINIX
          CARTINIY-VAL
          CARTINIY
          CARTINIZ-VAL
          CARTINIZ
          CARTINIROLL-VAL
          CARTINIROLL
          CARTINIPITCH-VAL
          CARTINIPITCH
          CARTINIYAW-VAL
          CARTINIYAW
          CARTDESX-VAL
          CARTDESX
          CARTDESY-VAL
          CARTDESY
          CARTDESZ-VAL
          CARTDESZ
          CARTDESROLL-VAL
          CARTDESROLL
          CARTDESPITCH-VAL
          CARTDESPITCH
          CARTDESYAW-VAL
          CARTDESYAW
          M-VAL
          M
          D-VAL
          D
          K-VAL
          K
          TASK_MA-VAL
          TASK_MA
          TASK_MB-VAL
          TASK_MB
          FIXEDFILTERWEIGHTS-VAL
          FIXEDFILTERWEIGHTS
          W0-VAL
          W0
          W1-VAL
          W1
          W2-VAL
          W2
          W3-VAL
          W3
          W4-VAL
          W4
          W5-VAL
          W5
          W6-VAL
          W6
          W7-VAL
          W7
))