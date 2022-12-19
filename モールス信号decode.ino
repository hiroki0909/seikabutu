# seikabutu

const int SWITCH = 2;
const int receive = 7;
String input;
String suzi;
int A = -1;
int sample, sample_1, sample_2;
int v, x;
int c = 0;
int n = 0;
int state ; //入力ピンの状態
int old_state = HIGH; //入力ピンの前の状態
int Highc;
int change;
int old_change = LOW;
int count = 0;

long t; //now_t - old_t
long x_1, x_2, x_3;
long old_t = 0;
long now_t = 0;
long old_x = 0; //自由短点
long now_x = 0;
long s_x;
long LOWtime; //LOW状態が続いた時間(ms)

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH, INPUT);
  pinMode(receive, INPUT);
}

void loop() {
  sample = digitalRead(receive);//チャタリング防止
  delay(1);
  sample_1 = digitalRead(receive);
  delay(1);
  sample_2 = digitalRead(receive);

  if (sample + sample_1 + sample_2 == 0){
    state = LOW;
  }else{
    state = HIGH;
  }

  if (Serial.available() > 0) { //文字列の受信
    input = Serial.readStringUntil('\n');
    if (input != -1 ) {
      Serial.print(input);
    }
  }

  if (input == "English") {
    if ((A != 0) && count == 0) {
      Serial.print("\n");
      Serial.println("英文モールス");
    } else if ((A != 0) && count != 0) {
      count = 0;
    }
    A = 0;
    
  }
  if (input == "Japanese") {
    if ((A != 1) && count == 0) {
      Serial.print("\n");
      Serial.println("和文モールス");
    } else if ((A != 1) && count != 0) {
      count = 0;
    }
    A = 1;
    
  }
  count++;

  change = digitalRead(SWITCH);
  if ((change == HIGH) && (old_change == LOW)) {
    x = x + 1;

    if (x == 1) {  //スイッチの操作
      v = 20;
      Serial.println("短点の値20ms");
      delay(150);
    }

    if (x == 2) {
      v = 50;
      Serial.println("短点の値50ms");
      delay(150);
    }
    if (x == 3) {
      v = 100;
      Serial.println("短点の値100ms");
      delay(150);
    }
    if (x == 4) {
      Serial.println("S検出");
      v = sss();
      Serial.print("短点の値は");
      Serial.println(v);
      Serial.print("S");
    }
    if(x > 5){
      x = 0;
    }
  }

  if (state == LOW && old_state == HIGH) { //信号がHIGHからLOWに変わったら
    
    old_t = now_t;
    now_t = millis();
    t = now_t - old_t;
    old_state = state;
    if (n != 0) {
      if (t / v >= 2) {
        if(A == 0) {
          morse_code();
        }else if(A == 1) {
          morse_code_jp();
        }
        suzi = "";
        if (t / v > 6) Serial.print(" ");
      }
    }
    else {
      n++;
    }
  }


  if (state == HIGH && old_state == LOW) { //信号がLOWからHIGHに変わったら
    old_t = now_t;
    now_t = millis();
    t = now_t - old_t;
    old_state = state;

    if (t / v <= 1) {
      suzi.concat("0");
    } else {
      suzi.concat("1");
    }
    Highc = 0;
  }

  if (state == HIGH) { //終了判定
    Highc++;
    //Highc = Highc + 3;
    delay(1);
    if (Highc > t * 8) {
      if (suzi != "") {
        if (A == 0) {
          morse_code();
        } else if (A == 1) {
          morse_code_jp();
        }
        Serial.print("\n");
        suzi = "";
      }
      old_t = 0;
      now_t = 0;
      t = 0;
      Highc = 0;
      n = 0;
      count = 0;
    }
  }
}

int sss() {
  while (c < 3) {
    state = digitalRead(receive);
    if (state == LOW && old_state == HIGH) {
      old_x = now_x;
      now_x = millis();
      old_state = state;
    }

    if (state == HIGH && old_state == LOW) { //信号がLOWからHIGHに変わったら
      old_x = now_x;
      now_x = millis();
      LOWtime = now_x - old_x;
      old_state = state;
      c++;
    }

    if (c == 1) {
      x_1 = LOWtime;
    }

    if (c == 2) {
      x_2 = LOWtime;
    }

    if (c == 3) {
      x_3 = LOWtime;
      s_x = (x_1 + x_2 + x_3) / 3 ;
    }
  }

  c = 0;
  Serial.print("短点の値は");
  Serial.print(s_x);
  Serial.println("ms");
  return s_x;
}

void morse_code_jp() {

  if (suzi.compareTo("11011") == 0) {
    Serial.print("ア");
  } else if (suzi.compareTo("01") == 0) {
    Serial.print("イ");
  } else if (suzi.compareTo("001") == 0) {
    Serial.print("ウ");
  } else if (suzi.compareTo("10111") == 0) {
    Serial.print("エ");
  } else if (suzi.compareTo("01000") == 0) {
    Serial.print("オ");
  } else if (suzi.compareTo("0100") == 0) {
    Serial.print("カ");
  } else if (suzi.compareTo("10100") == 0) {
    Serial.print("キ");
  } else if (suzi.compareTo("0001") == 0) {
    Serial.print("ク");
  } else if (suzi.compareTo("1011") == 0) {
    Serial.print("ケ");
  } else if (suzi.compareTo("1111") == 0) {
    Serial.print("コ");
  } else if (suzi.compareTo("10101") == 0) {
    Serial.print("サ");
  } else if (suzi.compareTo("11010") == 0) {
    Serial.print("シ");
  } else if (suzi.compareTo("11101") == 0) {
    Serial.print("ス");
  } else if (suzi.compareTo("01110") == 0) {
    Serial.print("セ");
  } else if (suzi.compareTo("1110") == 0) {
    Serial.print("ソ");
  } else if (suzi.compareTo("10") == 0) {
    Serial.print("タ");
  } else if (suzi.compareTo("0010") == 0) {
    Serial.print("チ");
  } else if (suzi.compareTo("0110") == 0) {
    Serial.print("ツ");
  } else if (suzi.compareTo("01011") == 0) {
    Serial.print("テ");
  } else if (suzi.compareTo("00100") == 0) {
    Serial.print("ト");
  } else if (suzi.compareTo("010") == 0) {
    Serial.print("ナ");
  } else if (suzi.compareTo("1010") == 0) {
    Serial.print("二");
  } else if (suzi.compareTo("0000") == 0) {
    Serial.print("ヌ");
  } else if (suzi.compareTo("1101") == 0) {
    Serial.print("ネ");
  } else if (suzi.compareTo("0011") == 0) {
    Serial.print("ノ");
  } else if (suzi.compareTo("1000") == 0) {
    Serial.print("ハ");
  } else if (suzi.compareTo("11001") == 0) {
    Serial.print("ヒ");
  } else if (suzi.compareTo("1100") == 0) {
    Serial.print("フ");
  } else if (suzi.compareTo("0") == 0) {
    Serial.print("ヘ");
  } else if (suzi.compareTo("100") == 0) {
    Serial.print("ホ");
  } else if (suzi.compareTo("1001") == 0) {
    Serial.print("マ");
  } else if (suzi.compareTo("00101") == 0) {
    Serial.print("ミ");
  } else if (suzi.compareTo("1") == 0) {
    Serial.print("ム");
  } else if (suzi.compareTo("10001") == 0) {
    Serial.print("メ");
  } else if (suzi.compareTo("10010") == 0) {
    Serial.print("モ");
  } else if (suzi.compareTo("011") == 0) {
    Serial.print("ヤ");
  } else if (suzi.compareTo("10011") == 0) {
    Serial.print("ユ");
  } else if (suzi.compareTo("11") == 0) {
    Serial.print("ヨ");
  } else if (suzi.compareTo("000") == 0) {
    Serial.print("ラ");
  } else if (suzi.compareTo("110") == 0) {
    Serial.print("リ");
  } else if (suzi.compareTo("10110") == 0) {
    Serial.print("ル");
  } else if (suzi.compareTo("111") == 0) {
    Serial.print("レ");
  } else if (suzi.compareTo("0101") == 0) {
    Serial.print("ロ");
  } else if (suzi.compareTo("101") == 0) {
    Serial.print("ワ");
  } else if (suzi.compareTo("0111") == 0) {
    Serial.print("ヲ");
  } else if (suzi.compareTo("01010") == 0) {
    Serial.print("ン");
  } else if (suzi.compareTo("01101") == 0) {
    Serial.print("ー");
  } else if (suzi.compareTo("00") == 0) {
    Serial.print("゛");
  } else if (suzi.compareTo("00110") == 0) {
    Serial.print("゜");
  } else if (suzi.compareTo("010101") == 0) {
    Serial.print("、");
  } 
}

void morse_code() {
  
  if (suzi.compareTo("01") == 0) {
    Serial.print("A");
  }else if (suzi.compareTo("1000") == 0) {
    Serial.print("B");
  }else if (suzi.compareTo("1010") == 0) {
    Serial.print("C");
  }else if (suzi.compareTo("100") == 0) {
    Serial.print("D");
  }else if (suzi.compareTo("0") == 0) {
    Serial.print("E");
  }else if (suzi.compareTo("0010") == 0) {
    Serial.print("F");
  }else if (suzi.compareTo("110") == 0) {
    Serial.print("G");
  }else if (suzi.compareTo("0000") == 0) {
    Serial.print("H");
  }else if (suzi.compareTo("00") == 0) {
    Serial.print("I");
  }else if (suzi.compareTo("0111") == 0) {
    Serial.print("J");
  }else if (suzi.compareTo("101") == 0) {
    Serial.print("K");
  }else if (suzi.compareTo("0100") == 0) {
    Serial.print("L");
  }else if (suzi.compareTo("11") == 0) {
    Serial.print("M");
  }else if (suzi.compareTo("10") == 0) {
    Serial.print("N");
  }else if (suzi.compareTo("111") == 0) {
    Serial.print("O");
  }else if (suzi.compareTo("0110") == 0) {
    Serial.print("P");
  }else if (suzi.compareTo("1101") == 0) {
    Serial.print("Q");
  }else if (suzi.compareTo("010") == 0) {
    Serial.print("R");
  }else if (suzi.compareTo("000") == 0) {
    Serial.print("S");
  }else if (suzi.compareTo("1") == 0) {
    Serial.print("T");
  }else if (suzi.compareTo("001") == 0) {
    Serial.print("U");
  }else if (suzi.compareTo("0001") == 0) {
    Serial.print("V");
  }else if (suzi.compareTo("011") == 0) {
    Serial.print("W");
  }else if (suzi.compareTo("1001") == 0) {
    Serial.print("X");
  }else if (suzi.compareTo("1011") == 0) {
    Serial.print("Y");
  }else if (suzi.compareTo("1100") == 0) {
    Serial.print("Z");
  }
}
