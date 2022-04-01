*************************************************************************************************************************
*   				      DEVELOPPEMENT DE LA STRUCTURE DU STM32						*
*		     		       DEVELOPPEMENT/STRUCTURE/BIBLIOTHEQUES/DOCUMENTATIONS				*
*						guetting_Started							*
*************************************************************************************************************************
Les 2 datasheets du stm32:
Le datasheet (organisation interne du micro, spécifications électrique, etc)                  [STM32L476xx]
   https://www.st.com/resource/en/datasheet/stm32l476rg.pdf
Le reference manual (fonctionnement détaillé de chaque périphérique et registres associés)    [RM0351]
   https://www.st.com/resource/en/reference_manual/dm00083560-stm32l4x5-and-stm32l4x6-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf

Bien sur si l’on développe sur carte nucleo pour nos tests il faut la petite documentation   [UM1724]
    https://www.st.com/en/evaluation-tools/nucleo-l476rg.html#documentation

Pour se connecter il nous faut le driver STLink/V2: stsw-link009_v2.0.2.     
    https://www.st.com/en/development-tools/stsw-link009.html

Pour programmer:
Nous allons choisir Atollic de TrueStudio car il permet de prendre en compte la compilation arm et la possibilité de programmer en C/C++ et
d'accéder au registre et d'intégrer une architecture personnalisée.
    https://www.st.com/en/development-tools/truestudio.html

La Bibliothèque HAL
recherche: stm32L4 library HAL
https://www.st.com/resource/en/user_manual/dm00173145-description-of-stm32l4l4-hal-and-lowlayer-drivers-stmicroelectronics.pdf
télécharger la library HAL 
https://www.st.com/en/embedded-software/stm32cubel4.html?ecmp=tt9470_gl_link_feb2019&rt=um&id=UM1884
(dépot git)
https://github.com/STMicroelectronics/STM32CubeL4
git clone https://github.com/STMicroelectronics/STM32CubeL4.git








































