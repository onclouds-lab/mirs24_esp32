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
}
