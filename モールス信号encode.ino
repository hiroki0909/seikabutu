String moji = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
char tontu[][5] = {"sl", "lsss", "lsls", "lss", "s", "ssls", "lls", "ssss", "ss", "slll", "lsl", "slss", "ll", "ls", "lll", "slls", "llsl", "sls", "sss", "l", "ssl", "sssl", "sll", "lssl", "lsll", "llss", "k"};

//点灯時間の設定 
int ton = 100; //単符 （s,１）
int tu = ton * 3; //長符（l,３）
int kyuhu = ton * 3; //文字間空白（３）
int kuhaku = ton * 4; //kyuhu+kuhaku = 単語間空白（k,７）

//LEDピン設定 13
const int ledPin = 13;
String tar;
//表示したい文字列設定（A~Z, 空白）

void setup() {
  pinMode(ledPin, OUTPUT);//13番ピン
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
   tar = String(char(Serial.read()));
  }
  for (int i = 0; i < tar.length(); i++) { //一文字単位でモールス符号の配列場所読み取り
    int s = moji.indexOf(tar[i]); //モールス符号が書かれた文字列の場所が返ってくる（0～）
    showChr(s);
  }
}

void showChr(int s) { //一文字分の符号読み取りと投げる
  int j = 0;
  while (tontu[s][j] != '\0') {
    showHugou(String(tontu[s][j]));//符号単位でshowHugouに投げる(ついでにChar→String変換)
    j++;
  }
  delay(kyuhu);//文字間空白
}

void showHugou(String chara) { //符号をもらって種類に応じて点灯させる。
int time = 0;

  if (chara.equals("s")) {//トン
    time = ton;
   tone(13, 37900);
   delay(time);
  // time = ton;
   
   //digitalWrite(ledPin, HIGH);
  } else if (chara.equals("l")) {//ツー
    time = tu;
     tone(13,37900);
     delay(time);
     //time = tu;
     
  } else if (chara.equals("k")) {//空白
    // time = kuhaku;
    delay(kuhaku);
     
  } else {
     delay(0);
   
  }
 // delay(time);//符号間休符
  noTone(13);
  delay(ton);

}
