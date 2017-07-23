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
  OnKeyDown = FormKeyDown
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
  object Bevel3: TBevel
    Left = 385
    Top = 45
    Width = 4
    Height = 541
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 416
    ExplicitTop = 192
    ExplicitHeight = 50
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
  object pnClient: TPanel
    Left = 389
    Top = 45
    Width = 995
    Height = 541
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    Visible = False
    DesignSize = (
      995
      541)
    object img: TImage
      Left = 6
      Top = 48
      Width = 979
      Height = 201
    end
    object Label1: TLabel
      Left = 6
      Top = 258
      Width = 122
      Height = 13
      Caption = 'Brauchbarkeit des Signals'
    end
    object mMsg: TMemo
      Left = 0
      Top = 384
      Width = 995
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
      Left = 495
      Top = 353
      Width = 114
      Height = 25
      Action = acCheckAllSignals
      TabOrder = 5
    end
    object cxAusgabe: TCheckBox
      Left = 923
      Top = 361
      Width = 66
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Ausgabe'
      TabOrder = 6
    end
    object cbCheckAllPosture: TComboBox
      Left = 615
      Top = 334
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
    object cbUsability: TComboBox
      Left = 134
      Top = 255
      Width = 123
      Height = 21
      Style = csDropDownList
      TabOrder = 8
      OnChange = acChangeUsabilityExecute
      Items.Strings = (
        '- nicht ausgew'#228'hlt -'
        'sehr gut'
        'brauchbar'
        'schlecht')
    end
    object cbCheckAllUsability: TComboBox
      Left = 615
      Top = 357
      Width = 114
      Height = 21
      Style = csDropDownList
      TabOrder = 9
      Items.Strings = (
        '- alle Signale -'
        'nur "sehr gute" Signale'
        'nur "brauchbare" Signale'
        'nur "schlechte" Signale')
    end
    object Button8: TButton
      Left = 784
      Top = 353
      Width = 123
      Height = 25
      Action = acCreateBeats
      TabOrder = 10
      Visible = False
    end
  end
  object pnLeft: TPanel
    Left = 0
    Top = 45
    Width = 385
    Height = 541
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 3
    object lvData: TListView
      Left = 0
      Top = 121
      Width = 385
      Height = 420
      Align = alClient
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
      TabOrder = 0
      ViewStyle = vsReport
      OnDblClick = lvDataDblClick
    end
    object pnDbFilter: TPanel
      Left = 0
      Top = 0
      Width = 385
      Height = 121
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DesignSize = (
        385
        121)
      object Label2: TLabel
        Left = 8
        Top = 6
        Width = 96
        Height = 13
        Caption = 'Datenbank-Filter'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
      end
      object Label3: TLabel
        Left = 8
        Top = 32
        Width = 36
        Height = 13
        Caption = 'Session'
      end
      object Label4: TLabel
        Left = 8
        Top = 59
        Width = 33
        Height = 13
        Caption = 'Person'
      end
      object Label5: TLabel
        Left = 198
        Top = 32
        Width = 39
        Height = 13
        Caption = 'Channel'
      end
      object Label6: TLabel
        Left = 198
        Top = 59
        Width = 66
        Height = 13
        Caption = 'Brauchbarkeit'
      end
      object Button7: TButton
        Left = 304
        Top = 90
        Width = 75
        Height = 25
        Action = acLoadDb
        Anchors = [akRight, akBottom]
        TabOrder = 0
      end
      object cbFSession: TComboBox
        Left = 56
        Top = 29
        Width = 113
        Height = 21
        Style = csDropDownList
        TabOrder = 1
      end
      object cbFPerson: TComboBox
        Left = 56
        Top = 56
        Width = 113
        Height = 21
        Style = csDropDownList
        TabOrder = 2
      end
      object cbFChannel: TComboBox
        Left = 266
        Top = 29
        Width = 113
        Height = 21
        Style = csDropDownList
        TabOrder = 3
      end
      object cbFUsability: TComboBox
        Left = 266
        Top = 56
        Width = 113
        Height = 21
        Style = csDropDownList
        TabOrder = 4
        Items.Strings = (
          '- nicht ausgew'#228'hlt -'
          'sehr gut'
          'brauchbar'
          'schlecht')
      end
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
    object acChangeUsability: TAction
      Caption = '&Brauchbarkeits-Merkmal '#228'ndern'
      OnExecute = acChangeUsabilityExecute
    end
    object acLoadDb: TAction
      Caption = '&Laden'
      OnExecute = acLoadDbExecute
    end
    object acCreateBeats: TAction
      Caption = 'Herzschl'#228'ge erzeugen'
      OnExecute = acCreateBeatsExecute
    end
  end
end
