object fmBasePeople: TfmBasePeople
  Left = 0
  Top = 0
  Caption = 'BaseForm People'
  ClientHeight = 542
  ClientWidth = 442
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel4: TBevel
    Left = 0
    Top = 97
    Width = 442
    Height = 8
    Align = alTop
    Shape = bsTopLine
    ExplicitLeft = 176
    ExplicitTop = 176
    ExplicitWidth = 50
  end
  object pnFilter: TPanel
    Left = 0
    Top = 0
    Width = 442
    Height = 97
    Align = alTop
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 0
    ExplicitTop = 2
    ExplicitWidth = 576
    object Label10: TLabel
      Left = 8
      Top = 33
      Width = 29
      Height = 13
      Caption = 'Filter'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 56
      Top = 35
      Width = 47
      Height = 13
      Caption = 'Ident von'
    end
    object Label12: TLabel
      Left = 164
      Top = 35
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label13: TLabel
      Left = 56
      Top = 61
      Width = 27
      Height = 13
      Caption = 'Name'
    end
    object laTabelle: TLabel
      Left = 56
      Top = 7
      Width = 47
      Height = 14
      Caption = 'laTabelle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object Label1: TLabel
      Left = 256
      Top = 35
      Width = 44
      Height = 13
      Caption = 'Alter von'
    end
    object Label2: TLabel
      Left = 368
      Top = 35
      Width = 13
      Height = 13
      Caption = 'bis'
    end
    object Label3: TLabel
      Left = 256
      Top = 61
      Width = 52
      Height = 13
      Caption = 'Geschlecht'
    end
    object edIdVon: TEdit
      Left = 111
      Top = 32
      Width = 45
      Height = 21
      TabOrder = 0
      OnExit = edIdVonExit
    end
    object edIdBis: TEdit
      Left = 186
      Top = 33
      Width = 45
      Height = 21
      TabOrder = 1
      OnExit = edIdVonExit
    end
    object edName: TEdit
      Left = 111
      Top = 59
      Width = 120
      Height = 21
      TabOrder = 2
      OnChange = edNameChange
      OnExit = edIdVonExit
    end
    object edAgeVon: TEdit
      Left = 315
      Top = 32
      Width = 45
      Height = 21
      TabOrder = 3
      OnExit = edIdVonExit
    end
    object edAgeBis: TEdit
      Left = 390
      Top = 33
      Width = 45
      Height = 21
      TabOrder = 4
      OnExit = edIdVonExit
    end
    object cbSex: TComboBox
      Left = 315
      Top = 60
      Width = 120
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 5
      Text = '- alle -'
      OnChange = edNameChange
      Items.Strings = (
        '- alle -'
        'm'#228'nnlich'
        'weiblich')
    end
  end
  object lvPeople: TListView
    Left = 0
    Top = 105
    Width = 442
    Height = 437
    Align = alClient
    Columns = <
      item
        Caption = 'Ident'
      end
      item
        Caption = 'Vorname'
        Width = 120
      end
      item
        Caption = 'Nachname'
        Width = 120
      end
      item
        Alignment = taCenter
        Caption = 'Alter'
      end
      item
        Alignment = taCenter
        Caption = 'Sex'
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = PopupMenu
    TabOrder = 1
    ViewStyle = vsReport
    OnClick = lvPeopleClick
    OnDblClick = lvPeopleDblClick
    ExplicitWidth = 405
  end
  object ActionListDiseases: TActionList
    Left = 160
    object acFilter: TAction
      Caption = 'Personen filtern'
      OnExecute = acFilterExecute
    end
    object acAdd: TAction
      Caption = 'Person hinzuf'#252'gen'
      OnExecute = acAddExecute
    end
    object acDel: TAction
      Caption = 'Person l'#246'schen'
      Enabled = False
      OnExecute = acDelExecute
    end
    object acChange: TAction
      Caption = 'Person &'#228'ndern'
      Enabled = False
      OnExecute = acChangeExecute
    end
    object acSelect: TAction
      Caption = 'Person ausw'#228'hlen'
      Enabled = False
      OnExecute = acSelectExecute
    end
  end
  object PopupMenu: TPopupMenu
    Left = 192
    object Erkrankunghinzufgen1: TMenuItem
      Action = acAdd
    end
    object Erkrankungndern1: TMenuItem
      Action = acChange
    end
    object Erkrankunglschen1: TMenuItem
      Action = acDel
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Personauswhlen1: TMenuItem
      Action = acSelect
    end
  end
  object tStartup: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tStartupTimer
    Left = 8
    Top = 56
  end
end
