object fmAddFile: TfmAddFile
  Left = 0
  Top = 0
  Caption = 'EKG-Signal speichern'
  ClientHeight = 674
  ClientWidth = 1177
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
    Width = 1177
    Height = 4
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = -189
    ExplicitWidth = 1081
  end
  object Bevel2: TBevel
    Left = 0
    Top = 629
    Width = 1177
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
    Width = 1177
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 943
    DesignSize = (
      1177
      41)
    object mInfo: TMemo
      Left = 8
      Top = 10
      Width = 1161
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
      ExplicitWidth = 927
    end
  end
  object pnBottom: TPanel
    Left = 0
    Top = 633
    Width = 1177
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 943
    DesignSize = (
      1177
      41)
    object Button1: TButton
      Left = 1079
      Top = 6
      Width = 90
      Height = 25
      Action = acClose
      Anchors = [akTop, akRight]
      TabOrder = 0
      ExplicitLeft = 845
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
      Width = 969
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 2
      Visible = False
      ExplicitWidth = 1076
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
      Top = 68
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
    object Label7: TLabel
      Left = 8
      Top = 95
      Width = 92
      Height = 13
      Caption = 'Lead 5+6 (change)'
    end
    object Label9: TLabel
      Left = 8
      Top = 278
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
      Top = 337
      Width = 33
      Height = 13
      Caption = 'Person'
    end
    object Label11: TLabel
      Left = 8
      Top = 310
      Width = 36
      Height = 13
      Caption = 'Session'
    end
    object Label12: TLabel
      Left = 8
      Top = 364
      Width = 39
      Height = 13
      Caption = 'Zustand'
    end
    object Label13: TLabel
      Left = 8
      Top = 391
      Width = 23
      Height = 13
      Caption = 'Lage'
    end
    object Label14: TLabel
      Left = 8
      Top = 441
      Width = 44
      Height = 13
      Caption = 'Blutdruck'
    end
    object Label15: TLabel
      Left = 172
      Top = 441
      Width = 4
      Height = 13
      Caption = '/'
    end
    object Label16: TLabel
      Left = 8
      Top = 468
      Width = 19
      Height = 13
      Caption = 'Puls'
    end
    object Label17: TLabel
      Left = 4
      Top = 531
      Width = 117
      Height = 13
      Caption = 'Kommentar zur Messung'
    end
    object Label3: TLabel
      Left = 8
      Top = 210
      Width = 145
      Height = 14
      Caption = 'Anzahl R-Peaks (visuell)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 122
      Width = 89
      Height = 13
      Caption = 'Leads abspeichern'
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
    object cbChannel56: TComboBox
      Left = 104
      Top = 92
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 1
      OnChange = cbChannelTest1Change
      Items.Strings = (
        '- keine Auswahl -'
        'Handr'#252'cken'
        'Halsschlagadern'
        'In den Ohren')
    end
    object cbPerson: TComboBox
      Left = 104
      Top = 334
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 5
    end
    object cbSession: TComboBox
      Left = 104
      Top = 307
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 4
    end
    object cbState: TComboBox
      Left = 104
      Top = 361
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 6
    end
    object cbPosture: TComboBox
      Left = 104
      Top = 388
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 7
    end
    object edBPSys: TEdit
      Left = 104
      Top = 438
      Width = 62
      Height = 21
      TabOrder = 8
    end
    object edBPDia: TEdit
      Left = 182
      Top = 438
      Width = 62
      Height = 21
      TabOrder = 9
    end
    object edPuls: TEdit
      Left = 104
      Top = 465
      Width = 62
      Height = 21
      TabOrder = 10
    end
    object mNote: TMemo
      Left = 0
      Top = 544
      Width = 273
      Height = 40
      Align = alBottom
      TabOrder = 11
    end
    object edRpeaks: TEdit
      Left = 182
      Top = 208
      Width = 62
      Height = 21
      TabOrder = 3
    end
    object cbSaveLeads: TComboBox
      Left = 104
      Top = 119
      Width = 140
      Height = 21
      Style = csDropDownList
      TabOrder = 2
      OnChange = cbChannelTest1Change
      Items.Strings = (
        'alle Leads der Datei speichern'
        'nur Lead56 speichern')
    end
  end
  object pnClient: TPanel
    Left = 277
    Top = 45
    Width = 900
    Height = 584
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 3
    object img12: TImage
      Left = 6
      Top = 6
      Width = 440
      Height = 110
    end
    object img34: TImage
      Left = 6
      Top = 119
      Width = 440
      Height = 110
    end
    object img56: TImage
      Left = 6
      Top = 235
      Width = 440
      Height = 110
    end
    object img2: TImage
      Left = 6
      Top = 351
      Width = 440
      Height = 110
    end
    object img3: TImage
      Left = 6
      Top = 468
      Width = 440
      Height = 110
    end
    object img4: TImage
      Left = 452
      Top = 6
      Width = 440
      Height = 110
    end
    object img5: TImage
      Left = 452
      Top = 120
      Width = 440
      Height = 110
    end
    object img6: TImage
      Left = 452
      Top = 235
      Width = 440
      Height = 110
    end
    object img7: TImage
      Left = 452
      Top = 352
      Width = 440
      Height = 110
    end
    object img8: TImage
      Left = 452
      Top = 468
      Width = 440
      Height = 110
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
