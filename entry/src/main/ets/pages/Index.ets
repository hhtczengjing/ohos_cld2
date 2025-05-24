import { CLD, DetectLanguage, Options } from '@devzeng/cld2';
import { util } from '@kit.ArkTS';

@Extend(Text)
function headerStyle() {
  .textAlign(TextAlign.Start)
  .width('100%')
  .padding({ left: 16, right: 16 })
  .fontSize(16)
  .fontColor('#7E8388')
}

@Extend(TextArea)
function inputStyle() {
  .width('100%')
  .borderRadius(0)
  .fontSize(16)
  .fontColor('#020F22')
}

@Extend(Text)
function outputStyle() {
  .textAlign(TextAlign.Start)
  .width('100%')
  .margin({ top: 10 })
  .padding({ left: 16, right: 16 })
  .fontSize(16)
  .fontColor('#020F22')
}

@Extend(Button)
function btnStyle() {
  .fontSize(16)
  .fontWeight(FontWeight.Regular)
  .backgroundColor('#344F9C')
  .width('35%')
}

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';
  @State result0: string = '';
  @State result1: string = '';
  @State result2: string = '';

  aboutToAppear(): void {
    this.readContent('test.txt').then((txt) => {
      this.message = txt;
    });
  }

  build() {
    Column() {
      Column() {
        Text('Input: ')
          .headerStyle()

        TextArea({ text: this.message })
          .inputStyle()
          .height('25%')
          .margin({ top: 10 })
      }
      .margin({ top: 10 })
      .width('100%')
      .padding({ left: 10, right: 10 })

      Row() {
        Button('读取配置')
          .fontSize(16)
          .fontWeight(FontWeight.Regular)
          .backgroundColor('#344F9C')
          .onClick(() => {
            const result = CLD.getContext();
            this.result0 = JSON.stringify(result);
          })

        Button('检测(同步)')
          .btnStyle()
          .onClick(() => {
            this.detectSync();
          })

        Button('检测(异步)')
          .btnStyle()
          .onClick(() => {
            this.detectAsync();
          })
      }
      .padding({ left: 10, right: 10 })
      .margin({ top: 20 })
      .justifyContent(FlexAlign.SpaceAround)
      .alignItems(VerticalAlign.Center)
      .width('100%')

      if (this.result0 || this.result1 || this.result2) {
        Scroll() {
          Column() {
            Text('Output')
              .headerStyle()

            if (this.result0) {
              Text(`result0: ${this.result0}`)
                .outputStyle()
                .margin({ top: 10 })
            }

            if (this.result1) {
              Text(`result1: ${this.result1}`)
                .outputStyle()
                .margin({ top: 10 })
            }

            if (this.result2) {
              Text(`result2: ${this.result2}`)
                .outputStyle()
                .margin({ top: 10 })
            }
          }
          .margin({ top: 20 })
          .justifyContent(FlexAlign.Start)
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')
        .layoutWeight(1)
      }
    }
    .height('100%')
    .width('100%')
  }

  readContent(name: string): Promise<string> {
    return new Promise((resolve, reject) => {
      getContext(this).resourceManager.getRawFileContent(name, (error, rawFile) => {
        if (error) {
          reject(error);
          return;
        }
        const textDecoder = util.TextDecoder.create('utf-8', { ignoreBOM: true });
        const txt = textDecoder.decodeToString(rawFile);
        resolve(txt);
      });
    });
  }

  private detectSync() {
    const result = CLD.detect(this.message);
    this.result1 = this.formatResult(result);
  }

  private detectAsync() {
    const options  = {
      isHTML       : false,
      languageHint : 'ENGLISH',
      encodingHint : 'UTF8UTF8',
      tldHint      : 'en',
      httpHint     : 'en'
    } as Options;
    CLD.detectAsync(this.message, options).then((result) => {
      this.result2 = this.formatResult(result);
    });
  }

  private formatResult(result: DetectLanguage): string {
    let str = "\n"
    const languages = result.languages;
    for (let index = 0; index < languages.length; index++) {
      const language = languages[index];
      str += `[${index+1}] name: ${language.name}, code: ${language.code}, percent: ${ language.percent}%\n`
    }
    return str
  }
}