object FormMain: TFormMain
  Left = 304
  Top = 190
  Caption = 'FormMain'
  ClientHeight = 361
  ClientWidth = 775
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 600
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnResize = FormResize
  DesignSize = (
    775
    361)
  PixelsPerInch = 96
  TextHeight = 13
  object LabelProgName: TLabel
    Left = 8
    Top = 8
    Width = 287
    Height = 20
    Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1085#1072#1103' '#1089#1080#1089#1090#1077#1084#1072' '#1048#1084#1087#1086#1088#1090'/'#1069#1082#1089#1087#1086#1088#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object ImagePlot: TImage
    Left = 303
    Top = 8
    Width = 464
    Height = 345
    Anchors = [akLeft, akTop, akRight, akBottom]
    Visible = False
    ExplicitHeight = 356
  end
  object Panel1: TPanel
    Left = 8
    Top = 34
    Width = 289
    Height = 247
    TabOrder = 0
    object EditCountry: TLabeledEdit
      Left = 10
      Top = 128
      Width = 121
      Height = 21
      EditLabel.Width = 37
      EditLabel.Height = 13
      EditLabel.Caption = #1057#1090#1088#1072#1085#1072
      TabOrder = 3
    end
    object ButtonSelect: TButton
      Left = 176
      Top = 78
      Width = 97
      Height = 25
      Caption = #1055#1086#1082#1072#1079#1072#1090#1100
      TabOrder = 7
      OnClick = ButtonSelectClick
    end
    object ButtonCntFromNam: TButton
      Left = 176
      Top = 171
      Width = 97
      Height = 25
      Caption = #1057#1090#1088#1072#1085#1099' '#1087#1086' '#1090#1086#1074
      TabOrder = 9
      OnClick = ButtonCntFromNamClick
    end
    object ButtonPlot: TButton
      Left = 176
      Top = 140
      Width = 97
      Height = 25
      Caption = #1043#1088#1072#1092#1080#1082
      TabOrder = 8
      OnClick = ButtonPlotClick
    end
    object EditProduct: TLabeledEdit
      Left = 10
      Top = 18
      Width = 121
      Height = 21
      EditLabel.Width = 30
      EditLabel.Height = 13
      EditLabel.Caption = #1058#1086#1074#1072#1088
      TabOrder = 0
    end
    object EditVolume: TLabeledEdit
      Left = 10
      Top = 54
      Width = 121
      Height = 21
      EditLabel.Width = 33
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1073#1098#1077#1084
      TabOrder = 1
    end
    object EditYear: TLabeledEdit
      Left = 10
      Top = 91
      Width = 121
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = #1043#1086#1076
      TabOrder = 2
    end
    object ButtonAdd: TButton
      Left = 176
      Top = 16
      Width = 97
      Height = 25
      Caption = #1047#1072#1087#1080#1089#1072#1090#1100
      TabOrder = 5
      OnClick = ButtonAddClick
    end
    object ButtonReset: TButton
      Left = 176
      Top = 47
      Width = 97
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      TabOrder = 6
      OnClick = ButtonResetClick
    end
    object GroupBox1: TGroupBox
      Left = 10
      Top = 155
      Width = 111
      Height = 83
      Caption = #1053#1072#1087#1088#1072#1074#1083#1077#1085#1080#1077
      TabOrder = 4
      object RadioImport: TRadioButton
        Left = 3
        Top = 16
        Width = 113
        Height = 17
        Caption = #1048#1084#1086#1088#1090
        TabOrder = 0
      end
      object RadioExport: TRadioButton
        Left = 3
        Top = 39
        Width = 113
        Height = 17
        Caption = #1069#1082#1089#1087#1086#1088#1090
        TabOrder = 1
      end
      object RadioAny: TRadioButton
        Left = 3
        Top = 62
        Width = 113
        Height = 17
        Caption = #1051#1102#1073#1086#1077
        Checked = True
        TabOrder = 2
        TabStop = True
      end
    end
    object ButtonDelete: TButton
      Left = 176
      Top = 109
      Width = 97
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100
      TabOrder = 10
      OnClick = ButtonDeleteClick
    end
  end
  object Panel3: TPanel
    Left = 8
    Top = 287
    Width = 289
    Height = 66
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 209
      Height = 13
      Caption = #1057#1090#1088#1072#1085#1072' '#1089' '#1085#1072#1080#1073#1086#1083#1100#1096#1080#1084' '#1086#1073#1098#1077#1084#1086#1084' '#1101#1082#1089#1087#1086#1088#1090#1072':'
    end
    object LabelLargestCnt: TLabel
      Left = 8
      Top = 27
      Width = 6
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object ButtonFind: TButton
      Left = 176
      Top = 27
      Width = 97
      Height = 25
      Caption = #1054#1087#1088#1077#1076#1077#1083#1080#1090#1100
      TabOrder = 0
      OnClick = ButtonFindClick
    end
  end
  object Grid: TStringGrid
    Left = 320
    Top = 8
    Width = 447
    Height = 345
    Anchors = [akLeft, akTop, akRight, akBottom]
    DefaultColWidth = 80
    FixedCols = 0
    RowCount = 2
    ScrollBars = ssHorizontal
    TabOrder = 2
    Visible = False
    OnDblClick = GridDblClick
    ColWidths = (
      80
      80
      80
      80
      80)
    RowHeights = (
      24
      24)
  end
end
