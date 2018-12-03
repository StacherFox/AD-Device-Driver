# AD Device Driver
## Sobre o Projeto

AD-Device-Driver é uma implementação de um device driver do tipo IIO para leitura de um conversor AD.

O conversor AD foi emulado por um Arduino Uno. 

## Compilando e Executando


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