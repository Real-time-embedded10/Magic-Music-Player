/*The principle of audio data increase or decrease is mainly to multiply the sampled data by a number or divide by a number, but pay 
attention to overflow processing.*/
/*If the value of the sampling point multiplied by the expansion factor is less than -32768 or greater than 32768, the value sampled 
here can only take -32768 or 32768.*/

//Increase the volume of the PCM data by twice.
int16_t pcm[1024] = read in some pcm data; //Take 1024 samples for PCM data.
int32_t pcmvol;
 for (ctr = 0; ctr < 1024; ctr++) {
     pcmvol = pcm[ctr] * 2; //Double the Volum
     //pcmvol = pcm[ctr] / 2; //Reducing the volum
     if (pcmval < 32767 && pcmval > -32768) {
         pcm[ctr] = pcmval
     } else if (pcmval > 32767) {
         pcm[ctr] = 32767;
     } else if (pcmval < -32768) {
         pcm[ctr] = -32768;
     }
 }