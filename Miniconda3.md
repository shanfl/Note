## miniconda3
### 环境
#### 验证环境
```
conda env list
```

#### 添加额外环境目录
```conda config --add envs_dirs M:\conda_envs```
<br>
```conda config --set envs_dirs M:\conda_envs```

#### 创建环境
```
# 使用--prefix创建的环境，激活时必须用完整路径
# 直接指定完整路径到M盘
conda create --prefix M:\conda_envs\opencv3 python=3.7
```

#### 激活 / 取消激活
```
# 激活时也要使用完整路径
conda activate M:\conda_envs\opencv3
```

```
#取消激活
conda deactivate
```

#### 临时指定环境目录
```
# 创建环境前设置环境变量
set CONDA_ENVS_PATH=M:\conda_envs

# 然后创建环境
conda create -n opencv3 python=3.7
```

#### 修改.condarc (永久配置)
``` yaml
envs_dirs:
  - M:\conda_envs
  - C:\Users\你的用户名\.conda\envs
  - C:\ProgramData\Anaconda3\envs
```
#### 卸载或删除环境
```
# 删除环境
conda remove --prefix M:\conda_envs\opencv3 --all

# 或者
conda env remove --prefix M:\conda_envs\opencv3
```
