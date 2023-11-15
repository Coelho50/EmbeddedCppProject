//------------ includes ----------------

#include <SPI.h> 

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

#include "PIR.hpp"
#include "peripherals.hpp"

//------------ defines, global variables and objects --------------

#define SS_PIN 21
#define RST_PIN 22

#define PIR_digital 4

#define pin_yellow
#define pin_green
#define pin_red
#define pin_buzzer

#define SIZE_BUFFER 18
#define MAX_SIZE_BLOCK 16


MFRC522::MIFARE_Key key;

MFRC522::StatusCode status;

MFRC522 reader(SS_PIN, RST_PIN); //Defining pins for SPI communication

Peripherals peripherals;

//--------------------- setup ------------------------------

void setup() {
  Serial.begin(115200);
  SPI.begin();

  peripherals.peripherals_init();

  reader.PCD_Init();
  delay(1000);
  Serial.println("\n");
  Serial.println("\nSystem initialized");
  Serial.println("Entering standby, please aproximate tag to activate motion sensor alarm");
}

//----------------------- functions -----------------------

//faz a leitura dos dados do cartão/tag
void show_data() {
  //imprime os detalhes tecnicos do cartão/tag
  reader.PICC_DumpDetailsToSerial(&(reader.uid));

  //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //buffer para colocar os dados ligos
  byte buffer[SIZE_BUFFER] = { 0 };

  //bloco que faremos a operação
  byte bloco = 1;
  byte tamanho = SIZE_BUFFER;


  //faz a autenticação do bloco que vamos operar
  status = reader.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(reader.uid));  //line 834 of reader.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(reader.GetStatusCodeName(status));
    return;
  }

  //faz a leitura dos dados do bloco
  status = reader.MIFARE_Read(bloco, buffer, &tamanho);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(reader.GetStatusCodeName(status));
    return;
  }

  Serial.print(F("\nDados bloco ["));
  Serial.print(bloco);
  Serial.print(F("]: "));

  //imprime os dados lidos
  for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++) {
    Serial.write(buffer[i]);
  }
  Serial.println(" ");
}






//menu para escolha da operação
int menu() {
  Serial.println(F("\nEscolha uma opção:"));
  Serial.println(F("0 - Read Data"));
  Serial.println(F("1 - Store data\n"));

  //fica aguardando enquanto o usuário nao enviar algum dado
  while (!Serial.available()) {};

  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while (Serial.available()) {
    if (Serial.read() == '\n') break;
    Serial.read();
  }
  return (op - 48);  //do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}





//faz a gravação dos dados no cartão/tag
void store_data() {
  //imprime os detalhes tecnicos do cartão/tag
  reader.PICC_DumpDetailsToSerial(&(reader.uid));
  // aguarda 30 segundos para entrada de dados via Serial
  Serial.setTimeout(30000L);
  Serial.println(F("Insira os dados a serem gravados com o caractere '#' ao final\n[máximo de 16 caracteres]:"));

  //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //buffer para armazenamento dos dados que iremos gravar
  byte buffer[MAX_SIZE_BLOCK] = "";
  byte bloco;         //bloco que desejamos realizar a operação
  byte tamanhoDados;  //tamanho dos dados que vamos operar (em bytes)

  //recupera no buffer os dados que o usuário inserir pela serial
  //serão todos os dados anteriores ao caractere '#'
  tamanhoDados = Serial.readBytesUntil('#', (char*)buffer, MAX_SIZE_BLOCK);
  //espaços que sobrarem do buffer são preenchidos com espaço em branco
  for (byte i = tamanhoDados; i < MAX_SIZE_BLOCK; i++) {
    buffer[i] = ' ';
  }

  bloco = 1;                   //bloco definido para operação
  String str = (char*)buffer;  //transforma os dados em string para imprimir
  Serial.println(str);

  //Authenticate é um comando para autenticação para habilitar uma comuinicação segura
  status = reader.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                    bloco, &key, &(reader.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(reader.GetStatusCodeName(status));
    delay(1000);
    return;
  }
  //else Serial.println(F("PCD_Authenticate() success: "));

  //Grava no bloco
  status = reader.MIFARE_Write(bloco, buffer, MAX_SIZE_BLOCK);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(reader.GetStatusCodeName(status));
    delay(1000);
    return;

  } else {
    Serial.println(F("MIFARE_Write() success: "));
  }
}


//--------------    LOOP     ---------------------------

void loop() {

  standby(); //Waits for card aproximation

  PIR motion_sensor;
  bool pir_activated = motion_sensor.pir_init(PIR_digital);

  if(!pir_activated){
    return;
  }//endif

  Serial.println("SYSTEM ACTIVATED");

  PRESENCE presence = motion_sensor.motion_alarm();
}  //endloop



