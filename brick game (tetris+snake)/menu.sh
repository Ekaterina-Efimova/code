#!/bin/bash

while true; do
  echo "1 - CLI"
  echo "2 - Desktop"
  echo "3 - Exit"
  echo -n "Введите ваш выбор: "
  read choice

  case $choice in
    1)
      while true; do
        echo "1 - Тетрис"
        echo "2 - Змейка"
        echo "3 - Назад"
        echo -n "Введите ваш выбор: "
        read game_choice

        case $game_choice in
          1)
            make run_tetris_cli
            if [ $? -eq 0 ]; then
              break
            else
              exit 1
            fi
            ;;
          2)
            make run_snake_cli
            if [ $? -eq 0 ]; then
              break
            else
              exit 1
            fi
            ;;
          3)
            break
            ;;
          *)
            echo "\n_____НЕВЕРНЫЙ__ВЫБОР_____\n"
            continue
            ;;
        esac
      done
      if [ $? -eq 0 ]; then
        continue
      else
        break
      fi
      ;;
    2)
      while true; do
        echo "1 - Тетрис"
        echo "2 - Змейка"
        echo "3 - Назад"
        echo -n "Введите ваш выбор: "
        read game_choice

        case $game_choice in
          1)
            make run_tetris_desktop
            if [ $? -eq 0 ]; then
              break
            else
              exit 1
            fi
            ;;
          2)
            make run_snake_desktop
            if [ $? -eq 0 ]; then
              break
            else
              exit 1
            fi
            ;;
          3)
            break
            ;;
          *)
            echo "\n_____НЕВЕРНЫЙ__ВЫБОР_____\n"
            continue
            ;;
        esac
      done
      if [ $? -eq 0 ]; then
        continue
      else
        break
      fi
      ;;
    3)
      echo "Выход"
      break
      ;;
    *)
      echo "\n_____НЕВЕРНЫЙ__ВЫБОР_____\n"
      continue
      ;;
  esac
done
