Int PIANOONLY=0
IF(TWM2=1) {
	ResetGS
	TINY=1
}
IF(MSGS=1) {
	ResetGS
}

IF(TINY=1) {
	Expression.Frequency(2);
	Modulation.Frequency(8);
	System.TimeBase=96
} ELSE {
	Expression.Frequency(1);
	Modulation.Frequency(1);
	System.TimeBase=12288
}

#PEDALON={Sub {r16y64,127}}
#PEDALOFF={r-32 y64,0 r32}

Int DB=0
IF(DEBUG=1) {
	#DEBUGMML1={Sub{@1v90V(127)'v90o5do6fo7a#o8d'}}
	#DEBUGMML2={Sub{@1v90V(127)'v90o5co6eo7g#o8c'}}
	#DEBUGMML3={Sub{@1v127V(127)'v127o4cdefgabo6cdefgab'}}
	TR(10)
		$M{n(MetronomeBell),}
		$m{n(MetronomeClick),}
		[1000
			Rythm{M4m4m4}
		]
}
Function TmpChangeR(tempo, len) {
	IF(len=0) {
		IF(DEBUG=1) {

			#DEBUGMML1
		}
		IF(!(IGNORETEMPO<>1)) {
			Tempo=tempo+TEMPODIFF
		}
	} ELSE {
		TmpChange(tempo, len)
		IF(DEBUG=1) {
			#DEBUGMML2
			r%(len)
		} ELSE {
			r%(len)
		}
	}
}

Function TmpChange(tempo, len) {
	IF(len=0) {
		IF(!(IGNORETEMPO<>1)) {
			Tempo=tempo+TEMPODIFF
		}
	} ELSE {
		IF(!(IGNORETEMPO<>1)) {
			Int TT1=Tempo
			Int TT2=tempo+TEMPODIFF
			Int TTDIFF=(TT2 - TT1)
			Int TTSTEP=TTDIFF
			IF(TTSTEP < 0) {
				TTSTEP=-TTDIFF
			}
			Int TTR=len / TTSTEP
			For(Int I=1; I < TTSTEP; I++) {
				Sub {
					r%(I*TTR)
					IF(TTDIFF < 0) {
						TT1 = TT1 - 1;
					} ELSE {
						TT1 = TT1 + 1;
					}
					Tempo = TT1;
				}
			}
			Sub{
				r%(len)
				Tempo=tempo+TEMPODIFF
			}
		}
	}
}

Int QTemp
Function QSet(value) {
	QTemp=value
}

Int ETemp
Function ESet(value) {
	ETemp=value
}

Int VTemp

Function VSet(value) {
	VTemp=value
}

Function Q(value) {
	Str MML="q"
	MML=MML+(value * QTemp / 100)
	MML
}

Function VVoice(Int v1, Int v2) {
	IF(PIANOONLY=0) {
		@(v1,v2)
	} ELSE {
		@(1,0)
	}
}

Function Dy(Int value) {
	Int D

	D=80*128+127

	IF(TWM2=1) {
		D=100*128+110
	} ELSE {
		IF(TIMIDITY=1) {
			D=105*128+120
		}
	}
	Int Base = 127 - (D % 128)
	Int Dynamic = D / 128
	Int V
	Int V2

	V = value - Base
	V = 127 - V
	V = V * 10 * Dynamic
	V = V / 1000
	V = 127 - V
	IF(V<0) {
		V=0
	}
	IF(V>127) {
		V=127
	}
 	Result = V
}

Function VV(value) {
	Str MML="v"
	MML=MML+(ExpVol(value))
	MML
}

Function ExpVol(value) {
	Int VTempAll
	RESULT=Dy(value)
}

Function ExpExp(value) {
	RESULT=Dy(value)
}

Function RandV(Int MIN, Int MAX) {
	Str MML="v"
	MML=MML+Random(ExpVol(MIN), ExpVol(MAX))
	MML
}

Str RMML
Function RandR(Int MIN, Int MAX) {
	Str MML="r"
	RMML=RMML+"r"
	Int VALUE=Random(0,10)
	IF(VALUE<5) {
		MML=MML+"-"
	} ELSE {
		RMML=RMML+"-"
	}
	Str RAND=Random(MIN,MAX)
	MML=MML+RAND
	RMML=RMML+RAND
	MML
}

Function SyncR() {
	Str MML=RMML
	RMML=""
	MML
}

Function BGHARP(Str MML) {
　　Str BUF=""
    Str FIRST=""
　　Str ML=""
　　Str M
　　Str R
    Str FM
    Int C=0

　　BUF=""
    R=""
　　For(Int i=1; MID(MML, i, 1)!=""; i++) {
　　　　M=MID(MML, i, 1)
//        Print("Count "+ C + " Str="+M)
　　　　IF(M="a"||M="b"||M="c"||M="d"||M="e"||M="f"||M="g") {
		C++
	  	IF(C<3) {
			FIRST=ML
			ML=FM+M
			FM=""
		} ELSE {
	　　　　　　R=R+"r"+Random(18,28)
　　　　　　　　	BUF=BUF+"Sub" + CHR(123)+R+ML+CHR(125)
	　　　　　　ML=M
		}
　　　　} ELSE {
		IF(C>0) {
	　　　　　　ML=ML+M
		} ELSE {
			FM=FM+M
		}
　　　　}
　　}
　　BUF=BUF+"Sub"+CHR(123)+R+ML+CHR(125)+FIRST
//    Print(BUF)
	IF(GAKUHU=1) {
		BUF="'"+MML+"'"
	}
　　BUF
}

Function E(value) {
	Expression(ExpExp(value))
}

Function ET(v11, v12, len1, v21, v22, len2, v31, v32, len3, v41, v42, len4, v51, v52, len5) {
	Int	NowTime;
	NowTime = Time;
	Expression.onTime(ExpExp(v11), ExpExp(v12), len1)
	IF(v21<>0) {
		Time=NowTime+len1
		Expression.onTime(ExpExp(v21), ExpExp(v22), len2)
		IF(v31<>0) {
			Time=NowTime+len1+len2
			Expression.onTime(ExpExp(v31), ExpExp(v32), len3)
			IF(v41<>0) {
				Time=NowTime+len1+len2+len3
				Expression.onTime(ExpExp(v41), ExpExp(v42), len4)
				IF(v51<>0) {
					Time=NowTime+len1+len2+len3+len4
					Expression.onTime(ExpExp(v51), ExpExp(v52), len5)
				}
			}
		}
	}
	Time=NowTime
}

Function EW(v11, v12, len1, v21, v22, len2, v31, v32, len3, v41, v42, len4, v51, v52, len5) {
	IF(len5<>0) {
		Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2, ExpExp(v31), ExpExp(v32), len3, ExpExp(v41), ExpExp(v42), len4, ExpExp(v51), ExpExp(v52), len5)
	} ELSE {
		IF(len4<>0) {
			Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2, ExpExp(v31), ExpExp(v32), len3, ExpExp(v41), ExpExp(v42), len4)
		} ELSE {
			IF(len3<>0) {
				Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2, ExpExp(v31), ExpExp(v32), len3)
			} ELSE {
				IF(len2<>0) {
					Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1, ExpExp(v21), ExpExp(v22), len2
					)
				} ELSE {
					IF(len1<>0) {
						Expression.onNoteWave(ExpExp(v11), ExpExp(v12), len1)
					}
				}
			}
		}
	}
}

Function Vibrate(delay1, depth1, delay2, depth2, delay3, depth3, delay4, depth4, delay5, depth5) {
	Int	NowTime;
	NowTime = Time;
	IF(delay1=0) {
		Modulation(depth1)
	} ELSE {
		Modulation.onNoteWave(0, 0, delay1 /2, 0, depth1, delay1/2)
		IF(delay2<>0) {
			Time=NowTime+delay1
			Modulation.onNoteWave(depth1, depth2, delay2)
			IF(delay3<>0) {
				Time=NowTime+delay1+delay2
				Modulation.onNoteWave(depth2, depth3, delay3)
				IF(delay4<>0) {
					Time=NowTime+delay1+delay2+delay3
					Modulation.onNoteWave(depth3, depth4, delay4)
					IF(delay5<>0) {
						Time=NowTime+delay1+delay2+delay3+delay4
						Modulation.onNoteWave(depth4, depth5, delay5)
					}
				}
			}
		}
	}
	Time=NowTime
}

#REV={
	IF(TWM2=1) {
		REV(50)
	}
}

#V_CELLO={
	#REV
	V(100)
	M(0)
	VVoice(Cello,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CELLO2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Cello,1)
	} ELSE {
		VVoice(Cello,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CELLO3={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Cello,2)
	} ELSE {
		VVoice(Cello,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CONTRABASS={
	#REV
	V(100)
	M(0)
	VVoice(Contrabass,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CONTRABASS2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Contrabass,1)
	} ELSE {
		VVoice(Contrabass,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CONTRABASS3={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Contrabass,2)
	} ELSE {
		VVoice(Contrabass,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}


#V_STRINGS1={
	#REV
	V(100)
	M(0)
	VVoice(Strings1,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_VIOLIN={
	#REV
	V(100)
	M(0)
	VVoice(Violin,0)
	QSet(100)
	VSet(127)
	ESet(127)
}
#V_VIOLIN2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Violin,1)
	} ELSE {
		VVoice(Violin,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}
#V_VIOLIN3={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Violin,2)
	} ELSE {
		VVoice(Violin,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}
#V_VIOLA={
	#REV
	V(100)
	M(0)
//	VVoice(Viola,0)
	VVoice(Violin,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_VIOLA2={
	#REV
	V(100)
	M(0)
	VVoice(Viola,1)
//	VVoice(Violin,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TRUMPET={
	#REV
	V(100)
	M(0)
	VVoice(Trumpet,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TRUMPET2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Trumpet,1)
	} ELSE {
		VVoice(Trumpet,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TROMBONE={
	#REV
	V(100)
	M(0)
	VVoice(Trombone,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_BASSTROMBONE={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Trombone,1)
	} ELSE {
		VVoice(Trumpet,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}


#V_HORN={
	#REV
	V(100)
	M(0)
	VVoice(FrenchHorn,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_HORN2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(FrenchHorn,1)
	} ELSE {
		VVoice(FrenchHorn,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_PICCOLO={
	#REV
	V(100)
	M(0)
	VVoice(Piccolo,0)
	QSet(100)
	VSet(127)
	ESet(127)
}
#V_FLUTE={
	#REV
	V(100)
	M(0)
	VVoice(Flute,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_FLUTE2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Flute,1)
	} ELSE {
		VVoice(Flute,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_FLUTE3={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Flute,2)
	} ELSE {
		VVoice(Flute,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CLARINET={
	#REV
	V(100)
	M(0)
	VVoice(Clarinet,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CLARINET2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Clarinet,1)
	} ELSE {
		VVoice(Clarinet,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CLARINET3={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Clarinet,2)
	} ELSE {
		VVoice(Clarinet,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_CLARINET4={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Clarinet,3)
	} ELSE {
		VVoice(Clarinet,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TIMPANI1={
	#REV
	V(100)
	M(0)
	VVoice(Timpani,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TIMPANI2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Timpani,1)
	} ELSE {
		VVoice(Timpani,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_PIZZ={
	#REV
	V(100)
	M(0)
	VVoice(PizzicatoStrings,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_BASSPIZZ={
	#REV
	V(100)
	M(0)
	VVoice(PizzicatoStrings,0)
	QSet(100)
	VSet(127)
	ESet(127)
}
#V_PIZZ2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(PizzicatoStrings,1)
	} ELSE {
		VVoice(PizzicatoStrings,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_OBOE={
	#REV
	V(100)
	M(0)
	VVoice(Oboe,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_OBOE2={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(Oboe,1)
	} ELSE {
		VVoice(Oboe,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_EHORN={
	#REV
	V(100)
	M(0)
	VVoice(EnglishHorn,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_BASSON={
	#REV
	V(100)
	M(0)
	VVoice(EnglishHorn,1)
	QSet(100)
	VSet(127)
	ESet(127)
}


#V_HARP={
	#REV
	V(100)
	M(0)
	VVoice(OrchestralHarp,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TREMORO={
	#REV
	V(100)
	M(0)
	IF(TIMIDITY=1) {
		VVoice(TremoloStrings,0)
	} ELSE {
		VVoice(Strings2,0)
	}
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_STRINGS2={
	#REV
	V(100)
	M(0)
	VVoice(Strings2,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_TUBA={
	#REV
	V(100)
	M(0)
	VVoice(Tuba,0)
	QSet(100)
	VSet(127)
	ESet(127)
}

#V_VOCALOID={
	#REV
	V(100)
	M(0)
	@1
	QSet(100)
	VSet(127)
	ESet(127)
	// for test Q


	q82
	// for test tempo 
	Tempo 120

}



// シンバルのロテート
Int CYMINIT=0
Int TRIINIT=0
Int SNAREINIT=0
Int GONGINIT=0
Int TAIHOINIT=0

Function Snare() {
	Int CC
	IF(TIMIDITY=0) {
		CC=Snare1
	} ELSE {
		CC=38+SNAREINIT
		IF(SNAREINIT=3) {
			SNAREINIT=0
		} ELSE {
			SNAREINIT=SNAREINIT+1
		}
	}
	Result=CC
}

Function Triangle() {
	Int CC
	IF(TRIINIT=0) {
		CC=80
		TRIINIT=1
	} ELSE {
			CC=81
		TRIINIT=0
	}
	Result=CC
}



Function Cymbal() {
	Int CC
	IF(CYMINIT=0) {
		CC=56
		CYMINIT=1
	} ELSE {
		CC=57
		CYMINIT=0
	}
	Result=CC
}

Function Gong() {
	Int CC
	CC=58+GONGINIT
	IF(GONGINIT=2) {
		GONGINIT=0
	} ELSE {
		GONGINIT=GONGINIT+1
	}
	Result=CC
}

Function Taiho() {
	Int CC
	CC=29+TAIHOINIT
	IF(TAIHOINIT=3) {
		TAIHOINIT=0
	} ELSE {
		TAIHOINIT=TAIHOINIT+1
	}
	Result=CC
}

#DRUMSET={
	#REV
	Key(0)
	PitchBendSensitivity(12)
	VVoice(OrchestraSet)
	$b{RandV(122,127) p%0 n(36),} //bd
	IF(TIMIDITY=1) {
		$X{RandV(125,127) p%0 n(Taiho()),} //fh70
	} ELSE {
		$X{RandV(125,127) p%0 n(36),} //bd
	}
	IF(TIMIDITY=1) {
		$s{RandV(105,127) p%0 n(Snare()),} //sd1
		$S{RandV( 80, 90) p%0 n(Snare()),} //sd2
	} ELSE {
		$s{RandV(105,127) p%0 n(38),} //sd1
		$S{RandV( 80, 90) p%0 n(40),} //sd2
	}

	IF(TIMIDITY=1) {
		$c{RandV(120,127) p%0 n(Cymbal()),} //classic cymbal
	} ELSE {
		$c{RandV(120,127) p%0 n(57),} //classic cymbal
	}
	IF(TIMIDITY=1) {
		$g{RandV(120,127) n(Gong()),} //gong
		$G{RandV(120,127) n(61),} //gong
		$o{RandV( 50, 70) p%0 n(Triangle()),}
		$O{p%0 n(Triangle()),}
		$h{RandV( 50, 70) p%0 n(MuteTriangle),}
	} ELSE {
		IF(USEGONG=1) {
			$g{RandV(120,127) p%-8192 n(57),} //gong
			$G{RandV(120,127) p%-8192 n(57),} //gong
		} ELSE {
			$g{RandV(120,127) p%0 n(57),} //gong
			$G{RandV(120,127) p%0 n(57),} //gong
		}
		$o{RandV( 50, 70) p%0 n(OpenTriangle),}
		$O{p%0 n(OpenTriangle),}
		$h{RandV( 50, 70) p%0 n(MuteTriangle),}
	}
}
