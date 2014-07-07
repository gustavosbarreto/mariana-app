
function drawLabel(posX, posY, width, height, code) {	
    var code = encode(code).join('');

    canvas.fillStyle = 'white';
    canvas.fillRect(posX, posY, width, height);

    var x = 0;
    var y = 0;

	canvas.debug(posX);
    for (var i = 0; i < code.length; i += 2) {
        var barWidth = parseInt(code.charAt(i));
        var spaceWidth = parseInt(code.charAt(i + 1));

        var finalX = x + posX;
        var finalY = y + posY;

        canvas.fillStyle = 'black';
        canvas.fillRect(finalX + 8, finalY, barWidth, height);
        canvas.stroke();
        x += barWidth + spaceWidth;
    }	
}


for (var row = 0; row < 20; row++) {
    for (var col = 0; col < 4; col++) {
		var margins = { left: 37, top: 26 };
		var labelWidth = 128;
		
		var x = col * labelWidth;
		var y = row * 36;
		x += margins.left;
		y += margins.top;

        drawLabel(x, y, labelWidth, 36, "" + (new Date).getTime());
    }
}

function encode(barcode) {
    var encodingTable = [212222, 222122, 222221, 121223, 121322, 131222, 122213, 122312, 132212, 221213, 221312, 231212, 112232, 122132, 122231,
        113222, 123122, 123221, 223211, 221132, 221231, 213212, 223112, 312131, 311222, 321122, 321221, 312212, 322112, 322211,
        212123, 212321, 232121, 111323, 131123, 131321, 112313, 132113, 132311, 211313, 231113, 231311, 112133, 112331, 132131,
        113123, 113321, 133121, 313121, 211331, 231131, 213113, 213311, 213131, 311123, 311321, 331121, 312113, 312311, 332111,
        314111, 221411, 431111, 111224, 111422, 121124, 121421, 141122, 141221, 112214, 112412, 122114, 122411, 142112, 142211,
        241211, 221114, 413111, 241112, 134111, 111242, 121142, 121241, 114212, 124112, 124211, 411212, 421112, 421211, 212141,
        214121, 412121, 111143, 111341, 131141, 114113, 114311, 411113, 411311, 113141, 114131, 311141, 411131, 211412, 211214, 211232, 23311120
    ];

    var bars = [];
    bars.add = function (i) {
        this.check = this.length == 0 ? i : this.check + i * this.length;
        this.push(encodingTable[i]);
    };

    bars.add(105); // Start Code C

    for (var i = 0; i < barcode.length; i++)
        bars.add(+barcode.substr(i++, 2));

    bars.push(encodingTable[bars.check % 103], encodingTable[encodingTable.length - 1]);

    return bars;
}
