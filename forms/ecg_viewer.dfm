object fmEcgViewer: TfmEcgViewer
  Left = 0
  Top = 0
  Caption = 'EcgViewer'
  ClientHeight = 640
  ClientWidth = 1081
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
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 1081
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -9
    ExplicitWidth = 1090
  end
  object Bevel3: TBevel
    Left = 337
    Top = 45
    Width = 4
    Height = 595
    Align = alLeft
    Shape = bsLeftLine
    ExplicitTop = 44
    ExplicitHeight = 596
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 1081
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      1081
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1065
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      BorderStyle = bsNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsItalic]
      Lines.Strings = (
        
          'EKG-Tool, erm'#246'glicht eine Vorab-Auswertung der EKG-Daten, soll s' +
          'p'#228'ter als Bestandteil des Gesamt-Frameworks integiert werden')
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object pnLeft: TPanel
    Left = 0
    Top = 45
    Width = 337
    Height = 595
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object Bevel4: TBevel
      Left = 0
      Top = 72
      Width = 337
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -2
      ExplicitTop = 48
    end
    object Label4: TLabel
      Left = 139
      Top = 187
      Width = 52
      Height = 13
      Caption = 'EKG-Daten'
    end
    object Label6: TLabel
      Left = 214
      Top = 187
      Width = 47
      Height = 13
      Caption = 'Erste Abl.'
    end
    object Label7: TLabel
      Left = 281
      Top = 187
      Width = 54
      Height = 13
      Caption = 'Zweite Abl.'
    end
    object Label9: TLabel
      Left = 148
      Top = 142
      Width = 35
      Height = 13
      Caption = 'Bereich'
    end
    object Label10: TLabel
      Left = 269
      Top = 142
      Width = 4
      Height = 13
      Caption = '-'
    end
    object Label8: TLabel
      Left = 146
      Top = 111
      Width = 39
      Height = 13
      Caption = 'Samples'
    end
    object Label11: TLabel
      Left = 269
      Top = 111
      Width = 4
      Height = 13
      Caption = '-'
    end
    object Bevel8: TBevel
      Left = 0
      Top = 349
      Width = 337
      Height = 4
      Align = alBottom
      Shape = bsBottomLine
      ExplicitLeft = -2
      ExplicitTop = 48
    end
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 337
      Height = 72
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 11
      object Label1: TLabel
        Left = 9
        Top = 2
        Width = 62
        Height = 13
        Caption = 'EKG Inputfile'
      end
      object btInputfile: TSpeedButton
        Left = 222
        Top = 14
        Width = 23
        Height = 23
        Caption = '...'
        OnClick = btInputfileClick
      end
      object Label3: TLabel
        Left = 291
        Top = 1
        Width = 38
        Height = 13
        Caption = 'Trenner'
      end
      object Label2: TLabel
        Left = 255
        Top = 1
        Width = 34
        Height = 13
        Caption = 'Format'
      end
      object edInputfile: TEdit
        Left = 8
        Top = 15
        Width = 214
        Height = 21
        TabOrder = 0
        Text = 'edInputfile'
      end
      object cbDelim: TComboBox
        Left = 292
        Top = 15
        Width = 36
        Height = 21
        Style = csDropDownList
        TabOrder = 2
        Items.Strings = (
          ';'
          ','
          '\t')
      end
      object cbFormat: TComboBox
        Left = 253
        Top = 15
        Width = 36
        Height = 21
        Style = csDropDownList
        TabOrder = 1
        Items.Strings = (
          '---'
          'ADS')
      end
      object cbLead: TComboBox
        Left = 222
        Top = 44
        Width = 107
        Height = 21
        Style = csDropDownList
        TabOrder = 3
        OnChange = cbLeadChange
        Items.Strings = (
          'Channel 1'
          'Channel 2'
          'Channel 3'
          'Channel 4'
          'Channel 5'
          'Channel 6'
          'Channel 7'
          'Channel 8'
          'Ableitung 12'
          'Ableitung 34'
          'Ableitung 56')
      end
    end
    object pbJob: TProgressBar
      Left = 8
      Top = 82
      Width = 320
      Height = 17
      TabOrder = 12
    end
    object btRead: TButton
      Tag = 1
      Left = 8
      Top = 105
      Width = 125
      Height = 25
      Action = acReadFile
      Caption = '&1 - Werte einlesen'
      TabOrder = 0
    end
    object btMovAv: TButton
      Tag = 3
      Left = 8
      Top = 200
      Width = 125
      Height = 25
      Action = acMovingAv
      Caption = '&3 - Kurven gl'#228'tten'
      TabOrder = 6
    end
    object btCut: TButton
      Tag = 2
      Left = 8
      Top = 136
      Width = 125
      Height = 25
      Action = acCutCurve
      Caption = '&2 - Kurven schneiden'
      TabOrder = 3
    end
    object edGl1: TEdit
      Left = 142
      Top = 202
      Width = 46
      Height = 21
      TabOrder = 7
    end
    object edGl2: TEdit
      Left = 212
      Top = 202
      Width = 46
      Height = 21
      TabOrder = 8
    end
    object edGl3: TEdit
      Left = 282
      Top = 202
      Width = 46
      Height = 21
      TabOrder = 9
    end
    object edCutVon: TEdit
      Left = 212
      Top = 138
      Width = 46
      Height = 21
      TabOrder = 4
    end
    object edCutBis: TEdit
      Left = 282
      Top = 138
      Width = 46
      Height = 21
      TabOrder = 5
    end
    object edVonSample: TEdit
      Left = 212
      Top = 107
      Width = 46
      Height = 21
      TabOrder = 1
    end
    object edBisSample: TEdit
      Left = 282
      Top = 107
      Width = 46
      Height = 21
      TabOrder = 2
    end
    object cxDropBegin: TCheckBox
      Left = 142
      Top = 229
      Width = 189
      Height = 17
      Caption = 'Anfangswerte '#252'berspringen'
      TabOrder = 10
    end
    object pnBottom: TPanel
      Left = 0
      Top = 353
      Width = 337
      Height = 242
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 13
      DesignSize = (
        337
        242)
      object laCls: TLabel
        Left = 317
        Top = 14
        Width = 18
        Height = 13
        Anchors = [akTop, akRight]
        Caption = 'CLS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        OnClick = laClsClick
      end
      object memo: TMemo
        Left = 0
        Top = 37
        Width = 337
        Height = 205
        Align = alBottom
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
      object btSave2: TButton
        Left = 158
        Top = 6
        Width = 158
        Height = 25
        Caption = '5 - EKG in DB speichern (Test)'
        TabOrder = 1
        OnClick = btSave2Click
      end
    end
    object btQrsTurns: TButton
      Left = 191
      Top = 303
      Width = 125
      Height = 25
      Caption = 'Qrs-Punkte anzeigen'
      TabOrder = 14
      OnClick = btQrsTurnsClick
    end
    object btRpeaks: TButton
      Left = 206
      Top = 272
      Width = 125
      Height = 25
      Caption = 'R-Peaks anzeigen'
      TabOrder = 15
      OnClick = btRpeaksClick
    end
    object btSave: TButton
      Tag = 4
      Left = 8
      Top = 286
      Width = 125
      Height = 25
      Action = acSaveArffFile
      TabOrder = 16
    end
  end
  object pnClient: TPanel
    Left = 341
    Top = 45
    Width = 740
    Height = 595
    Align = alClient
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
    object imgEcg: TImage
      Left = 0
      Top = 0
      Width = 740
      Height = 152
      Align = alTop
      PopupMenu = PopupMenu1
      OnMouseDown = imgEcgMouseDown
      OnMouseMove = imgEcgMouseMove
      OnMouseUp = imgEcgMouseUp
      ExplicitLeft = 2
      ExplicitTop = 2
      ExplicitWidth = 728
    end
    object BevelEcg: TBevel
      Left = 0
      Top = 152
      Width = 740
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 280
      ExplicitTop = 240
      ExplicitWidth = 50
    end
    object imgDeriv1: TImage
      Left = 0
      Top = 156
      Width = 740
      Height = 152
      Align = alTop
      ExplicitLeft = -4
      ExplicitTop = 352
      ExplicitWidth = 728
    end
    object imgDeriv2: TImage
      Left = 0
      Top = 312
      Width = 740
      Height = 152
      Align = alTop
      ExplicitLeft = -4
      ExplicitTop = 308
      ExplicitWidth = 728
    end
    object BevelAbl1: TBevel
      Left = 0
      Top = 308
      Width = 740
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = 6
      ExplicitTop = 304
      ExplicitWidth = 728
    end
    object Bevel6: TBevel
      Left = 0
      Top = 464
      Width = 740
      Height = 4
      Align = alTop
      Shape = bsTopLine
      ExplicitLeft = -4
      ExplicitTop = 344
      ExplicitWidth = 728
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 272
    Top = 8
  end
  object OpenDialog: TOpenDialog
    Filter = 'TXT-Dateien|*.txt|CSV-Dateien|*.csv'
    Left = 336
    Top = 8
  end
  object tDetails: TTimer
    Enabled = False
    Interval = 100
    Left = 456
    Top = 8
  end
  object SaveDialog: TSaveDialog
    Left = 488
    Top = 8
  end
  object PopupMenu1: TPopupMenu
    Left = 496
    Top = 96
    object estSavePic1: TMenuItem
      Caption = 'Test Save Pic'
      OnClick = estSavePic1Click
    end
  end
  object SaveDialog2: TSaveDialog
    Left = 528
    Top = 96
  end
  object ActionList1: TActionList
    Left = 304
    Top = 8
    object acReadFile: TAction
      Caption = 'Werte einlesen'
      OnExecute = acReadFileExecute
    end
    object acCutCurve: TAction
      Caption = 'Kurve schneiden'
      OnExecute = acCutCurveExecute
    end
    object acMovingAv: TAction
      Caption = 'Kurven gl'#228'tten'
      OnExecute = acMovingAvExecute
    end
    object acSaveArffFile: TAction
      Caption = 'Save Beats in ARFF-File'
      OnExecute = acSaveArffFileExecute
    end
  end
end
