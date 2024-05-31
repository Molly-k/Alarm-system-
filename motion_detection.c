#include "stm32f4xx_hal.h"
if (!code_set) {
SSD1306_Clear();
SSD1306_GotoXY(0, 0);
SSD1306_Puts("Set Code:", &Font_11x18, 1);
SSD1306_UpdateScreen();
input_index = 0;
memset(user_code, 0, sizeof(user_code)); //
Réinitialiser user_code while(input_index < 6) { // Accepter jusqu'à 6 chiffres
pour le code
key = Get_Key();
HAL_Delay(100); // Debounce delay
if(key == 'A' && input_index >= 4) { // 'A': fin de
saisie, avec au moins 4 chiffres
user_code[input_index] = '\0'; // Terminer la
chaîne de caractères
code_set = 1;
SSD1306_Clear();
SSD1306_GotoXY(0, 0);
SSD1306_Puts("Code Set", &Font_11x18, 1);
SSD1306_UpdateScreen();
HAL_Delay(2000); // Donner du temps pour lire
le message
break; // Sortir de la boucle de saisie du code
} else if (key != NO_KEY && key != 'A') {
if(input_index < 6) { // Ajouter le chiffre au code
user_code[input_index++] = key;
SSD1306_GotoXY(input_index * 11, 30);
SSD1306_Puts("*", &Font_11x18, 1); //
Afficher un astérisque pour le chiffre entré
SSD1306_UpdateScreen();
}
}}
}
else {
// Une fois le code défini, permettre
l'armement/désarmement
SSD1306_Clear();
SSD1306_GotoXY(0, 0);
SSD1306_Puts(armed ? "Disarm:" : "Arm:",
&Font_11x18, 1);
SSD1306_UpdateScreen();
input_index = 0;memset(input_code, 0, sizeof(input_code)); //
Réinitialiser input_code
while(input_index < strlen(user_code)) {
key = Get_Key();
HAL_Delay(100); // Debounce delay
if(key != NO_KEY) {
input_code[input_index++] = key;
SSD1306_GotoXY(input_index * 11, 30);
SSD1306_Puts("*", &Font_11x18, 1);
SSD1306_UpdateScreen();
}
if(input_index == strlen(user_code)) {
input_code[input_index] = '\0'; // Terminer la chaîne
de caractères
if(strcmp(input_code, user_code) == 0) { // Si le
code entré correspond au code utilisateur
armed = !armed;
SSD1306_Clear();
SSD1306_GotoXY(0, 0);
SSD1306_Puts(armed ? "System Armed" :
"System Disarmed", &Font_11x18, 1);
SSD1306_UpdateScreen();
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,
armed ? GPIO_PIN_SET : GPIO_PIN_RESET); // LED
rouge pour armé, verte pour désarméHAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,
armed ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
}
}
}if (armed) {
// Afficher "System Armed" et allumer la LED rouge
SSD1306_Clear();
SSD1306_GotoXY(0, 0);
SSD1306_Puts("System Armed", &Font_11x18, 1);
SSD1306_UpdateScreen();
HAL_Delay(2000);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2,
GPIO_PIN_SET); // LED rouge
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3,
GPIO_PIN_RESET); // LED verte éteinte
// Compte à rebours de 10 secondes avant d'activer la
détection de mouvement
showCountdown(10);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_SET); // Activer le buzzer pour simuler la
détection
HAL_Delay(6000); // Simuler attente pour
désarmement
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_RESET);
HAL_Delay(6000); // Continuer la simulation
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_SET);
HAL_Delay(6000); // Encore simulationHAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_RESET);
HAL_Delay(3000); // Attente supplémentaire
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_SET);
HAL_Delay(6000); // Simuler attente pour
désarmement
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_RESET);
}
else {
SSD1306_Clear();
SSD1306_GotoXY(0, 0);
SSD1306_Puts("Wrong Code", &Font_11x18, 1);
SSD1306_UpdateScreen();
HAL_Delay(2000);
input_index = 0;
memset(input_code, 0, sizeof(input_code)); }while (armed) {
if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12) ==
GPIO_PIN_SET) { // Si mouvement détecté
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_SET); // Activer le buzzer
HAL_Delay(60000); // Attendre 60 secondes
// Après l'attente, désactiver le buzzer
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9,
GPIO_PIN_RESET); // Désactiver le buzzer
break; // Sortir de la boucle si l'alarme a été
déclenchée
}
HAL_Delay(100);
}