## miniconda3

#### 添加额外环境目录
```conda config --add envs_dirs M:\conda_envs```
<br>
```conda config --set envs_dirs M:\conda_envs```

#### 创建环境
`
# 直接指定完整路径到M盘
conda create --prefix M:\conda_envs\opencv3 python=3.7
`
