#!/bin/bash

# Script para instalar las dependencias necesarias para Stellar
# Este script instala todas las dependencias del sistema requeridas

# No salir en el primer error, queremos que el instalador continúe aunque falten algunos paquetes
# set -e

# Limpiar cualquier lista de paquetes fallidos anteriores
rm -f /tmp/failed_packages

echo "=== Instalando dependencias del sistema ==="
echo "PROGRESS:30"

# Actualizar el sistema
apt update

echo "PROGRESS:40"

# Instalar dependencias básicas de compilación
apt install -y build-essential cmake pkg-config
if [ $? -ne 0 ]; then echo "build-essential cmake pkg-config" >> /tmp/failed_packages; fi

# Instalar dependencias de Qt6 WebEngine (esenciales)
apt install -y \
    qt6-base-dev \
    qt6-webengine-dev \
    qt6-tools-dev
if [ $? -ne 0 ]; then echo "qt6-base-dev qt6-webengine-dev qt6-tools-dev" >> /tmp/failed_packages; fi

# Instalar dependencias gráficas esenciales
apt install -y \
    libgl1-mesa-dev \
    libx11-dev \
    libxcb1-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev
if [ $? -ne 0 ]; then echo "libgl1-mesa-dev libx11-dev libxcb1-dev libxkbcommon-dev libxkbcommon-x11-dev" >> /tmp/failed_packages; fi

# Instalar dependencias esenciales para WebEngine
apt install -y \
    libdrm2 \
    libgbm1 \
    libnss3-dev \
    libxcomposite-dev \
    libxdamage-dev \
    libxrandr-dev
if [ $? -ne 0 ]; then echo "libdrm2 libgbm1 libnss3-dev libxcomposite-dev libxdamage-dev libxrandr-dev" >> /tmp/failed_packages; fi

echo "PROGRESS:70"

echo "=== Dependencias instaladas (es posible que algunos paquetes no se hayan encontrado) ==="
echo "PROGRESS:100"

# Construir el proyecto
echo ""
echo "=== Compilando Stellar Nexus ==="
if [ -f build.sh ]; then
    chmod +x build.sh
    sh build.sh
fi

# Ejecutar la aplicación
echo ""
echo "=== Iniciando Stellar Nexus==="
if [ -f build/stellar ]; then
    chmod +x build/stellar
    ./build/stellar "$@"
else
    echo "Error: No se encontró el ejecutable. La compilación puede haber fallado."
    exit 1
fi

# Siempre retornar éxito
exit 0
