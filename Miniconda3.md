## miniconda3
### 环境
#### 添加额外环境目录
```conda config --add envs_dirs M:\conda_envs```
<br>
```conda config --set envs_dirs M:\conda_envs```

#### 创建环境
```
# 直接指定完整路径到M盘
conda create --prefix M:\conda_envs\opencv3 python=3.7
```

#### 激活
```
# 激活时也要使用完整路径
conda activate M:\conda_envs\opencv3
```

#### 临时指定环境目录
```
# 创建环境前设置环境变量
set CONDA_ENVS_PATH=M:\conda_envs

# 然后创建环境
conda create -n opencv3 python=3.7
```

#### 修改.condarc (永久配置)
```
envs_dirs:
  - M:\conda_envs
  - C:\Users\你的用户名\.conda\envs
  - C:\ProgramData\Anaconda3\envs
```
