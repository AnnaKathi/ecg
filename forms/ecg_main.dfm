object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'fmMain'
  ClientHeight = 608
  ClientWidth = 729
  Color = clWindow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object img3: TImage
    Left = 8
    Top = 467
    Width = 170
    Height = 55
  end
  object img2: TImage
    Left = 8
    Top = 406
    Width = 170
    Height = 55
  end
  object img1: TImage
    Left = 8
    Top = 345
    Width = 170
    Height = 55
  end
  object img4: TImage
    Left = 8
    Top = 528
    Width = 170
    Height = 55
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 589
    Width = 729
    Height = 19
    Panels = <
      item
        Width = 250
      end
      item
        Width = 250
      end
      item
        Width = 250
      end>
  end
  object mInfo: TMemo
    Left = 184
    Top = 0
    Width = 545
    Height = 589
    Align = alRight
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object btTestMySql: TButton
    Left = 8
    Top = 8
    Width = 170
    Height = 25
    Caption = 'Test &MySql People'
    TabOrder = 2
    OnClick = btTestMySqlClick
  end
  object btTestCsv: TButton
    Left = 8
    Top = 39
    Width = 170
    Height = 25
    Caption = 'Test &Csv-Klasse'
    TabOrder = 3
    OnClick = btTestCsvClick
  end
  object btTestMath: TButton
    Left = 8
    Top = 70
    Width = 170
    Height = 25
    Caption = 'Test &Math-Klasse'
    TabOrder = 4
    OnClick = btTestMathClick
  end
  object btTestArray: TButton
    Left = 8
    Top = 101
    Width = 170
    Height = 25
    Caption = 'Test Array-Klasse'
    TabOrder = 5
    OnClick = btTestArrayClick
  end
  object btTestData: TButton
    Left = 8
    Top = 132
    Width = 170
    Height = 25
    Caption = 'Test Data-Klasse'
    TabOrder = 6
    OnClick = btTestDataClick
  end
  object btTestEcg: TButton
    Left = 8
    Top = 163
    Width = 170
    Height = 25
    Caption = 'Test Ecg-Klasse'
    TabOrder = 7
    OnClick = btTestEcgClick
  end
  object btEcgViewer: TButton
    Left = 8
    Top = 238
    Width = 170
    Height = 25
    Caption = 'Ecg Viewer'
    TabOrder = 8
    OnClick = btEcgViewerClick
  end
  object btAddLead: TButton
    Left = 8
    Top = 207
    Width = 170
    Height = 25
    Caption = 'Add File to DB'
    TabOrder = 9
    OnClick = btAddLeadClick
  end
  object btViewSignal: TButton
    Left = 8
    Top = 263
    Width = 170
    Height = 25
    Caption = 'Signal Viewer'
    TabOrder = 10
    OnClick = btViewSignalClick
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 648
    Top = 8
  end
end
