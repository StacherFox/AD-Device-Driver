# AD Device Driver
## Sobre o Projeto

AD-Device-Driver é uma implementação de um device driver do tipo IIO para leitura de um conversor AD.

O conversor AD foi emulado por um Arduino Uno.

 ![scheme](/img/scheme.jpg)



## Compilando e Executando

### Raspberry Pi


Antes de carregar este módulo é necessário carregar alguns módulos do sistema:

```
# modprobe industrialio
# modprobe i2c-dev
```

Para instanciar o drive i2c, pode ser executado o seguinte código:
```
# echo AD 0x72 >> /sys/bus/i2c/devices/i2c-1/new_device
```

Para compilar é apenas necessário executar o comando `make` no terminal e então carregar o módulo gerado:
```
# make
# insmod AD.ko
```

Após a compilação, Na mesma pasta estará o arquivo *Read_AD* que faz a leitura dos arquivos criados com o Framework IIO.

### Arduino

É necessário carregar o arquivo `Arduino_Slave.ino` em um Arduino.

No Arduino conecte o pino central de dois potenciômetros nos pinos A0 e A1 para se medir um nível de tensão variável.

## Leitura dos Valores

O programa *Read_AD* que estará presente após a compilação se encarrega de abrir os arquivos gerados do dispositivo e mostrar os valores lidos.
