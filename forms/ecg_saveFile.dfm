object fmAddFile: TfmAddFile
  Left = 0
  Top = 0
  Caption = 'EKG-Signal speichern'
  ClientHeight = 674
  ClientWidth = 943
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
  object Bevel1: TBevel
    Left = 0
    Top = 41
    Width = 943
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -189
    ExplicitWidth = 1081
  end
  object Bevel2: TBevel
    Left = 0
    Top = 629
    Width = 943
    Height = 4
    Align = alBottom
    Shape = bsBottomLine
    ExplicitTop = 49
    ExplicitWidth = 892
  end
  object Bevel3: TBevel
    Left = 273
    Top = 45
    Width = 4
    Height = 584
    Align = alLeft
    Shape = bsLeftLine
    ExplicitLeft = 240
    ExplicitTop = 152
    ExplicitHeight = 50
  end
  object pnInfo: TPanel
    Left = 0
    Top = 0
    Width = 943
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      943
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 927
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
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 633
    Width = 943
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 712
    DesignSize = (
      943
      41)
    object Button1: TButton
      Left = 845
      Top = 6
      Width = 90
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
    end
    object Button2: TButton
      Left = 8
      Top = 6
      Width = 90
      Height = 25
      Action = acSave
      TabOrder = 1
    end
    object pbJob: TProgressBar
      Left = 104
      Top = 6
      Width = 735
      Height = 25
      TabOrder = 2
      Visible = False
    end
  end
  object pnLeft: TPanel
    Left = 0
    Top = 45
    Width = 273
    Height = 584
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = -2
    ExplicitTop = 43
    DesignSize = (
      273
      584)
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 60
      Height = 14
      Caption = 'EKG-Datei'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton1: TSpeedButton
      Left = 244
      Top = 23
      Width = 23
      Height = 22
      Action = acLoadFile
      Anchors = [akTop, akRight]
      ExplicitLeft = 196
    end
    object Label2: TLabel
      Left = 8
      Top = 76
      Width = 82
      Height = 14
      Caption = 'Einstellungen'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 8
      Top = 108
      Width = 73
      Height = 13
      Caption = 'Test-Channel 1'
    end
    object Label4: TLabel
      Left = 8
      Top = 135
      Width = 73
      Height = 13
      Caption = 'Test-Channel 2'
    end
    object Label5: TLabel
      Left = 8
      Top = 162
      Width = 72
      Height = 13
      Caption = 'Lead Brust eng'
    end
    object Label6: TLabel
      Left = 8
      Top = 189
      Width = 61
      Height = 13
      Caption = 'Lead R'#252'cken'
    end
    object Label7: TLabel
      Left = 8
      Top = 216
      Width = 83
      Height = 13
      Caption = 'Lead Handr'#252'cken'
    end
    object Label9: TLabel
      Left = 8
      Top = 271
      Width = 99
      Height = 14
      Caption = 'Personen-Daten'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 8
      Top = 330
      Width = 33
      Height = 13
      Caption = 'Person'
    end
    object Label11: TLabel
      Left = 8
      Top = 303
      Width = 36
      Height = 13
      Caption = 'Session'
    end
    object Label12: TLabel
      Left = 8
      Top = 357
      Width = 39
      Height = 13
      Caption = 'Zustand'
    end
    object Label13: TLabel
      Left = 8
      Top = 384
      Width = 23
      Height = 13
      Caption = 'Lage'
    end
    object Label14: TLabel
      Left = 8
      Top = 434
      Width = 44
      Height = 13
      Caption = 'Blutdruck'
    end
    object Label15: TLabel
      Left = 172
      Top = 434
      Width = 4
      Height = 13
      Caption = '/'
    end
    object Label16: TLabel
      Left = 8
      Top = 461
      Width = 19
      Height = 13
      Caption = 'Puls'
    end
    object Label17: TLabel
      Left = 8
      Top = 499
      Width = 117
      Height = 13
      Caption = 'Kommentar zur Messung'
    end
    object edEkg: TEdit
      Left = 8
      Top = 23
      Width = 236
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      Text = 'edEkg'
    end
    object cbChannelTest1: TComboBox
      Left = 104
      Top = 105
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 1
      OnChange = cbChannelTest1Change
    end
    object cbChannelTest2: TComboBox
      Left = 104
      Top = 132
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 2
      OnChange = cbChannelTest1Change
    end
    object cbChannel12: TComboBox
      Left = 104
      Top = 159
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 3
      OnChange = cbChannelTest1Change
    end
    object cbChannel34: TComboBox
      Left = 104
      Top = 186
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 4
      OnChange = cbChannelTest1Change
    end
    object cbChannel56: TComboBox
      Left = 104
      Top = 213
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 5
      OnChange = cbChannelTest1Change
    end
    object cbPerson: TComboBox
      Left = 104
      Top = 327
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 7
    end
    object cbSession: TComboBox
      Left = 104
      Top = 300
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 6
    end
    object cbState: TComboBox
      Left = 104
      Top = 354
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 8
    end
    object cbPosture: TComboBox
      Left = 104
      Top = 381
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 9
    end
    object edBPSys: TEdit
      Left = 104
      Top = 431
      Width = 62
      Height = 21
      TabOrder = 10
    end
    object edBPDia: TEdit
      Left = 182
      Top = 431
      Width = 62
      Height = 21
      TabOrder = 11
    end
    object edPuls: TEdit
      Left = 104
      Top = 458
      Width = 62
      Height = 21
      TabOrder = 12
    end
    object mNote: TMemo
      Left = 0
      Top = 512
      Width = 273
      Height = 72
      Align = alBottom
      TabOrder = 13
    end
  end
  object pnClient: TPanel
    Left = 277
    Top = 45
    Width = 666
    Height = 584
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitLeft = 279
    ExplicitTop = 47
    object img1: TImage
      Left = 6
      Top = 6
      Width = 515
      Height = 107
    end
    object img2: TImage
      Left = 6
      Top = 119
      Width = 515
      Height = 107
    end
    object img3: TImage
      Left = 6
      Top = 232
      Width = 515
      Height = 107
    end
    object img4: TImage
      Left = 6
      Top = 345
      Width = 515
      Height = 107
    end
    object img5: TImage
      Left = 6
      Top = 458
      Width = 515
      Height = 107
    end
    object Label8: TLabel
      Left = 536
      Top = 0
      Width = 114
      Height = 13
      Caption = 'Anzahl R-Peaks (visuell)'
    end
    object edRpeaks1: TEdit
      Left = 552
      Top = 48
      Width = 81
      Height = 21
      TabOrder = 0
    end
    object edRpeaks2: TEdit
      Left = 552
      Top = 163
      Width = 81
      Height = 21
      TabOrder = 1
    end
    object edRpeaks3: TEdit
      Left = 552
      Top = 272
      Width = 81
      Height = 21
      TabOrder = 2
    end
    object edRpeaks4: TEdit
      Left = 552
      Top = 384
      Width = 81
      Height = 21
      TabOrder = 3
    end
    object edRpeaks5: TEdit
      Left = 552
      Top = 496
      Width = 81
      Height = 21
      TabOrder = 4
    end
  end
  object ActionList: TActionList
    Left = 360
    object acClose: TAction
      Caption = '&Abbrechen'
      OnExecute = acCloseExecute
    end
    object acSave: TAction
      Caption = 'EKG &speichern'
      Enabled = False
      OnExecute = acSaveExecute
      OnUpdate = acSaveUpdate
    end
    object acLoadFile: TAction
      Caption = '...'
      ShortCut = 16506
      OnExecute = acLoadFileExecute
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 328
  end
  object OpenDialog: TOpenDialog
    Filter = 'ADS-EKG-File|*.txt'
    Left = 392
  end
end
