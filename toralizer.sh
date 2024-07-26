#! /bin/bash

export LD_PRELOAD="/home/henrique/Scripts/C++_Banter/Toralizer/toralizer.so" 
${@}

unset LD_PRELOAD; 