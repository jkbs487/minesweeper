# MineSweeper 扫雷


## Introduction

最近LeetCode上做了一道扫雷相关的算法题，于是就想做一个扫雷的小项目...

## Envoirment

- OS：Ubuntu 20.04
- Complier: g++ 9.3.0

## Build

./start.sh [length] [width]

## Version


### version 0.0.1
- 实现基本的扫雷功能，通过标准输出展示扫雷界面
- 每次从标准输入两个整数代表下次要点击的位置坐标

### version 0.0.2
- 增加了命令行输入，通过来脚本输入扫雷棋盘的长和宽
- 修复了无法判断扫雷成功的bug
- 修复扫雷结束不显示所有雷区的bug
- 限制了棋盘的大小，目前是最大 40 * 40
- 优化了扫雷界面，外围增加了坐标数字
