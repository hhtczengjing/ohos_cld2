# ohos_cld2

Language detection for HarmonyOS. Based on the [CLD2](https://github.com/CLD2Owners/cld2) (Compact Language Detector) library from Google.

## 安装

```shell
ohpm i @devzeng/cld2
```

OpenHarmony ohpm 环境配置等更多内容，请参考[如何安装 OpenHarmony ohpm 包](https://ohpm.openharmony.cn/#/cn/help/downloadandinstall)

## 使用

```javascript
import { CLD } from '@devzeng/cld2';

// 读取参数配置
const result = CLD.getContext();
console.log(JSON.stringify(result));

// 同步检测
const result = CLD.detect("Hello World");
console.log(JSON.stringify(result));

// 异步检测
CLD.detectAsync("Hello World").then((result) => {
    console.log(JSON.stringify(result));
});
```

## 致谢

项目实现来源于 [node-cld](https://github.com/dachev/node-cld) 项目