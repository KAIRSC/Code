VERSION 5.00
Begin VB.Form VBExample 
   Caption         =   "VBExample"
   ClientHeight    =   3120
   ClientLeft      =   48
   ClientTop       =   348
   ClientWidth     =   5532
   LinkTopic       =   "Form1"
   ScaleHeight     =   3120
   ScaleWidth      =   5532
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Write"
      Height          =   372
      Left            =   1680
      TabIndex        =   6
      Top             =   2400
      Width           =   1332
   End
   Begin VB.TextBox Text1 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1030
         SubFormatType   =   1
      EndProperty
      Height          =   372
      Left            =   240
      TabIndex        =   5
      Text            =   "0"
      Top             =   2400
      Width           =   1092
   End
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   3000
      Top             =   600
   End
   Begin VB.Label Label3 
      Caption         =   "Hint: Enable the auto connect option in the connection  menu in order to automatically establish a connection."
      Height          =   1092
      Left            =   2640
      TabIndex        =   7
      Top             =   1080
      Width           =   2772
   End
   Begin VB.Label Label2 
      Caption         =   "Result:"
      Height          =   252
      Left            =   360
      TabIndex        =   4
      Top             =   120
      Width           =   732
   End
   Begin VB.Label Label1 
      Height          =   252
      Index           =   2
      Left            =   360
      TabIndex        =   3
      Top             =   1560
      Width           =   1692
   End
   Begin VB.Label Label1 
      Height          =   252
      Index           =   1
      Left            =   360
      TabIndex        =   2
      Top             =   1080
      Width           =   1692
   End
   Begin VB.Label Result 
      Height          =   252
      Left            =   1320
      TabIndex        =   1
      Top             =   120
      Width           =   1692
   End
   Begin VB.Label Label1 
      Height          =   252
      Index           =   0
      Left            =   360
      TabIndex        =   0
      Top             =   600
      Width           =   1692
   End
End
Attribute VB_Name = "VBExample"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public m_svr1 As Object
Dim status As Integer



Private Sub Command1_Click()
   m_svr1.Register(0) = Text1   ' Store the value in
                                ' Modbus Poll register array index 0
                                ' Physical not the same register used in read
   status = m_svr1.PresetMultipleRegisters(1, 2, 1)
   ' Write 1 value (m_svr1.Register(0)) to address 2 (40003) slave ID 1
   
End Sub

Private Sub Form_Load()
   Set m_svr1 = CreateObject("mbpoll.Document")
   status = m_svr1.CreateRequest(1, 3, 0, 3, 1000)  ' Read 3 Holding Register
                                                    ' From addr. 0 (40001)
                                                    ' Slave ID 1
                                                    ' Each 1000ms
   ' These 3 values are stored in m_svr1.Register(0) to 2
   ' Values are always store from index 0 no matter if we read from e.g.
   ' addr. 10 (40011)
                                                    
   'status = m_svr1.ShowWindow      ' Use this command to show Modbus Poll

End Sub

Private Sub Timer1_Timer()
   Result = m_svr1.ReadResult
   Label1(0) = m_svr1.Register(0)
   Label1(1) = m_svr1.Register(1)
   Label1(2) = m_svr1.Register(2)
End Sub
