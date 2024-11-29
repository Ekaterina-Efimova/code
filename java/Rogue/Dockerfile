# Используем образ Ubuntu
FROM ubuntu:latest

# Устанавливаем необходимые пакеты
RUN apt-get update && apt-get install -y \
    openjdk-11-jdk \
    maven \
    curl \
    locales \
    && apt-get clean

RUN locale-gen ru_RU.UTF-8  
ENV LANG ru_RU.UTF-8  
ENV LANGUAGE ru_RU:ru  
ENV LC_ALL ru_RU.UTF-8  

# Устанавливаем переменные окружения для Maven
ENV MAVEN_VERSION=3.8.4
ENV MAVEN_HOME=/usr/share/maven

# Скачиваем и устанавливаем Maven
RUN apt-get update && apt-get install -y maven

# Копируем исходный код в Docker-контейнер
COPY . /usr/src
WORKDIR /usr/src/src

# Собираем проект
RUN mvn clean package  -Dfile.encoding=UTF-8

# Указываем команду для запуска приложения
CMD ["mvn", "exec:java", "-Dexec.mainClass=Rogue.App"]