void imu_setup(){
 if(!bno.begin())
  {
    // 初期化に失敗した場合、エラーメッセージを表示して停止
    while(1);
  }

  // 外部クリスタルを使用する設定（より精度が安定します）
  bno.setExtCrystalUse(true);

  delay(1000);
}
  
void get_imu_value(){
  accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  quat = bno.getQuat();
}

void input_imu_value(){
  rosidl_runtime_c__String__assign(&imu_msg.header.frame_id, "imu_link");
  // 線形加速度
  imu_msg.linear_acceleration.x = accel.x();
  imu_msg.linear_acceleration.y = accel.y();
  imu_msg.linear_acceleration.z = accel.z();

  // 角速度
  imu_msg.angular_velocity.x = gyro.x();
  imu_msg.angular_velocity.y = gyro.y();
  imu_msg.angular_velocity.z = gyro.z();

  // 姿勢（クォータニオン）
  imu_msg.orientation.w = quat.w();
  imu_msg.orientation.x = quat.x();
  imu_msg.orientation.y = quat.y();
  imu_msg.orientation.z = quat.z();

  // 共分散を0で初期化（使用しない場合）
  imu_msg.orientation_covariance[0] = -1;
  imu_msg.angular_velocity_covariance[0] = -1;
  imu_msg.linear_acceleration_covariance[0] = -1;
}