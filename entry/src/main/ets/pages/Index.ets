import { CLD } from '@devzeng/cld2';

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
  @State result1: string = '';
  @State result2: string = '';

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

      if (this.result1 || this.result2) {
        Column() {
          Text('Output')
            .headerStyle()

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
    }
    .height('100%')
    .width('100%')
  }

  private detectSync() {
    const result = CLD.detect(this.message);
    this.result1 = JSON.stringify(result);
  }

  private detectAsync() {
    this.result2 = '暂不支持';
  }
}