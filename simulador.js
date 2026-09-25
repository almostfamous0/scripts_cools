
function simulacao_ano(init_val, percent=0.08, acerto=0.5, sim_meses=30){
    const inicio = init_val;
	let meses = 12;
	let lucro = 0, break_condition = 0, trading_times = 0;

	while(meses){
		for(let i = 0; i < 30; i++)
		{
			var aposta = init_val*percent;
			win = Math.random()*100>>0;
			trading_times += 1;
			console.log(` TRADING_TIMES: ${trading_times}`);

			if (win <= acerto*100){
				init_val += aposta*0.8;
				lucro += aposta*0.8;
			}

			if (win > acerto*100){
				init_val -= aposta;
				lucro -= aposta;
			}

			if (init_val <= inicio*0.09)
				break_condition = 1;
				break;
		}

	if (break_condition)
		break;

	meses--;
	}

	if(break_condition){
    	console.log(`\x1b[31mVoce teve um prejuizo de R$ ${init_val-inicio},00.  E sua banca vale: R$ ${init_val},00 agora!\n\x1b[0m\n >>> [ + ] Isso Ocorreu com ${13-meses} Meses!`);
	return false;
	}

	else {
		console.log(`\x1b[32mParabens!  Voce teve um lucro de R$ ${init_val-inicio},00 e banca: ${init_val}\n Foram feitas ${trading_times} APOSTAS!\n\x1b[0m`);
	return true;
	}
}

let casos_bons = 0, total = 1000;

for (let i = 0; i < total; i++)
	if (simulacao_ano(1000))
		casos_bons++;

console.log(`Houveram ${casos_bons}/${total} CASOS BONS`);
