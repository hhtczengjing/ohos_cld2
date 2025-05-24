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