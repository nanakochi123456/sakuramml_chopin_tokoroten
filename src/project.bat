SET TITLE=‚Æ‚±‚ë‚Ä‚ñ
SET CONFIG=tokoroten.cfg
SET EFFECT= -EFchorus=d,1 -EFreverb=d,1 --volume=50, --drum-power=50
rem  --no-fast-panning --no-fast-decay --anti-alias --polyphony=512 --no-polyphony-reduction -EFresamp=n -EFvlpf=m --decay-time=300
SET PLAYOPTION=--output-stereo --sampling-freq=44100 %EFFECT% --output-16bit
SET OPTION=--output-stereo --sampling-freq=96000 --output-24bit %EFFECT%
rem SET OPTION=--output-stereo --sampling-freq=48000 --output-16bit %EFFECT%
rem SET MML=003.mml
SET MML=tokoroten.mml
SET MMLREPLACE1=Int VOCALOID=1/Int VOCALOID=0,Int TIMIDITY=0/Int TIMIDITY=1,Int MSGS=1/Int MSGS=0/Int TWM2=1/Int TWM2=0/Int DEBUG=1/Int DEBUG=0

SET MML1=tokoroten_all.mml

SET MIDI1=tokoroten_all.mid

SET MIDI1PLAY=1
