//ノードのタイマーコールバック関数
void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    //PID計算
    PID_control();
    //エンコーダーデータを格納
    enc_msg.data.data[0] = count_l;
    enc_msg.data.data[1] = count_r;
    //電圧観測
    vlt_watch();
    //imu取得
    get_imu_value();
    input_imu_value();

    curr_vel_msg.data.data[0] = l_vel;
    curr_vel_msg.data.data[1] = r_vel;
    vlt_msg.data.data[0] = accel.x();
    vlt_msg.data.data[1] = gyro.x();
    rcl_publish(&enc_pub, &enc_msg, NULL);
    rcl_publish(&vlt_pub, &vlt_msg, NULL);
    rcl_publish(&curr_vel_pub, &curr_vel_msg, NULL);
    rcl_publish(&imu_pub, &imu_msg, NULL);
  }
}

// cmd_velメッセージのコールバック関数
void cmd_vel_Callback(const void * msgin) {
  const geometry_msgs__msg__Twist * vel_msg = (const geometry_msgs__msg__Twist *)msgin;

  // linear.x と angular.z のデータを取得
  linear_x = vel_msg->linear.x;
  angular_z = vel_msg->angular.z;

  //  目標速度計算
  r_vel_cmd = linear_x + WHEEL_BASE / 2 * angular_z;
  l_vel_cmd = linear_x - WHEEL_BASE / 2 * angular_z;
}

//TODO: 消してサービスに移行
//パラメーター更新のコールバック関数
void param_Callback(const void * msgin){
  const mirs_msgs__msg__BasicParam * param_msg = (const mirs_msgs__msg__BasicParam *)msgin;

  // linear.x と angular.z のデータを取得
  WHEEL_RADIUS = param_msg->wheel_radius;
  WHEEL_BASE = param_msg->wheel_base;
  RKP = param_msg->rkp;
  RKI = param_msg->rki;
  RKD = param_msg->rkd;
  LKP = param_msg->lkp;
  LKI = param_msg->lki;
  LKD = param_msg->lkd;
}