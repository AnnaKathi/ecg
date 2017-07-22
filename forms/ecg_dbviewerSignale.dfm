object fmViewSignal: TfmViewSignal
  Left = 0
  Top = 0
  Caption = 'Datenbank-Viewer: Signale'
  ClientHeight = 631
  ClientWidth = 1384
  Color = clWindow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 1384
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -205
    ExplicitWidth = 1177
  end
  object Bevel2: TBevel
    Left = 0
    Top = 586
    Width = 1384
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitLeft = -205
    ExplicitTop = 627
    ExplicitWidth = 1177
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1384
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      1384
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1368
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        'Eine EKG-Datei laden und in die Datenbank speichern.')
      ParentFont = False
      TabOrder = 0
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 590
    Width = 1384
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    DesignSize = (
      1384
      41)
    object Button1: TButton
      Left = 1286
      Top = 6
      Width = 90
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 6
      Width = 1272
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      Visible = False
    end
  end
  object lvSignale: TListView
    Left = 0
    Top = 45
    Width = 441
    Height = 541
    Align = alLeft
    Columns = <
      item
        Caption = 'Nr'
        Width = 35
      end
      item
        Caption = 'Session'
        Width = 90
      end
      item
        Caption = 'Person'
        Width = 80
      end
      item
        Caption = 'Channel'
        Width = 75
      end
      item
        Caption = 'Zustand'
        Width = 75
      end
      item
        Caption = 'Lage'
        Width = 75
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
    OnDblClick = lvSignaleDblClick
  end
  object pnClient: TPanel
    Left = 441
    Top = 45
    Width = 943
    Height = 541
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitLeft = 552
    ExplicitTop = 88
    ExplicitWidth = 577
    ExplicitHeight = 457
    object img: TImage
      Left = 6
      Top = 48
      Width = 923
      Height = 201
    end
    object mMsg: TMemo
      Left = 0
      Top = 384
      Width = 943
      Height = 157
      Align = alBottom
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object Button2: TButton
      Left = 6
      Top = 353
      Width = 75
      Height = 25
      Action = acPrevSignal
      TabOrder = 1
    end
    object Button3: TButton
      Left = 87
      Top = 353
      Width = 75
      Height = 25
      Action = acNextSignal
      TabOrder = 2
    end
    object Button4: TButton
      Left = 168
      Top = 353
      Width = 75
      Height = 25
      Action = acShowSignal
      TabOrder = 3
    end
    object Button5: TButton
      Left = 272
      Top = 353
      Width = 121
      Height = 25
      Action = acCalcRpeaks
      TabOrder = 4
    end
    object Button6: TButton
      Left = 399
      Top = 353
      Width = 114
      Height = 25
      Action = acCheckAllSignals
      TabOrder = 5
    end
    object cxAusgabe: TCheckBox
      Left = 519
      Top = 361
      Width = 66
      Height = 17
      Caption = 'Ausgabe'
      TabOrder = 6
    end
    object cbCheckSignale: TComboBox
      Left = 399
      Top = 326
      Width = 114
      Height = 21
      Style = csDropDownList
      TabOrder = 7
      Items.Strings = (
        '- alle Postures -'
        'nur liegend'
        'nur sitzend'
        'nur stehend'
        'nur gehend')
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 328
  end
  object ActionList: TActionList
    Left = 360
    object acClose: TAction
      Caption = '&Abbrechen'
      OnExecute = acCloseExecute
    end
    object acPrevSignal: TAction
      Caption = 'Prev'
      ShortCut = 16470
      OnExecute = acPrevSignalExecute
    end
    object acNextSignal: TAction
      Caption = 'Next'
      ShortCut = 16462
      OnExecute = acNextSignalExecute
    end
    object acShowSignal: TAction
      Caption = 'Show'
      ShortCut = 16397
      OnExecute = acShowSignalExecute
    end
    object acCalcRpeaks: TAction
      Caption = 'R-Peaks berechnen'
      ShortCut = 16466
      OnExecute = acCalcRpeaksExecute
    end
    object acCheckAllSignals: TAction
      Caption = 'Alle Signale pr'#252'fen'
      OnExecute = acCheckAllSignalsExecute
    end
  end
end
