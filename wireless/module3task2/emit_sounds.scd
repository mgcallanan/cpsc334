(
// Start server
s.boot;
a = Platform.resourceDir +/+ "sounds/rooster.wav";
b = Platform.resourceDir +/+ "sounds/dog.wav";

// Define sound
SynthDef( \sin,	{ | amp = 0.01, freq = 333, trig = 1 |
	var env, sig;
	env = EnvGen.kr( Env.asr( 0.001, 0.9, 0.001 ), trig, doneAction: 0 );
	sig = LFTri.ar( [ freq, freq * 0.999 ], 0.0, amp ) * env;
	Out.ar( [ 0 ], sig * 0.6 );
}).add;
h = Synth( \sin, [ \amp, 0.4 ] );

// Manipulate pitch of sound with incoming OSC messages
q = OSCFunc( { | msg, time, addr, port |
	"Received Mary pulse!".postln;
	c = Buffer.read(s, a, action: { arg buffer;
		("After update:" + buffer.numFrames).postln;
		x = { PlayBuf.ar(1, buffer, BufRateScale.kr(buffer)) }.play;
	});
}, '/marypulse' );

r = OSCFunc( { | msg, time, addr, port |
	"Received Maansi pulse!".postln;
	d = Buffer.read(s, b, action: { arg buffer;
		("After update:" + buffer.numFrames).postln;
		x = { PlayBuf.ar(1, buffer, BufRateScale.kr(buffer)) }.play;
	});
}, '/maansipulse' );

// Play tone with incoming OSC pulse messages
t = OSCFunc( { | msg, time, addr, port |
	var pyFreq = msg[1].asFloat;
	( "freq is " + pyFreq).postln;
	h.set( \freq, pyFreq);
}, '/distance');
)
