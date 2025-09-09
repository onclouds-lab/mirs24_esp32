void imu_setup(){
 if(!bno.begin())
  {
    // 初期化に失敗した場合、エラーメッセージを表示して停止
    while(1);
  }

  // 外部クリスタルを使用する設定（より精度が安定します）
  bno.setExtCrystalUse(true);
  imu_msg.data.size = 9; // メッセージ配列のサイズを2に設定
  imu_msg.data.data = (double *)malloc(imu_msg.data.size * sizeof(double)); // 配列のメモリを確保
  imu_msg.data.data[0] = 0;
  imu_msg.data.data[1] = 0;
  imu_msg.data.data[2] = 0;
  imu_msg.data.data[3] = 0;
  imu_msg.data.data[4] = 0;
  imu_msg.data.data[5] = 0;
  imu_msg.data.data[6] = 0;
  imu_msg.data.data[7] = 0;
  imu_msg.data.data[8] = 0;
  delay(1000);
}
  
void get_imu_value(){
  accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
}
