function numeroAleatorio(min, max){
    return Math.random() * (max + min) + '%';
}


function desvia(t){
    var btn = t

    btn.style.position = 'absolute'
    btn.style.bottom = numeroAleatorio(1, 85)
    btn.style.left = numeroAleatorio(1,85)

}


function sim(){
    var des = document.querySelector("h1")

    des.innerHTML = 'DESCULPA, EU FUI BURRO E VACILEI PARA KRL, NÉ?'

/*
    var a = document.querySelector('button')
    var b = document.querySelector('button#btn')
    var c = document.querySelector('img')


    a.style.display = 'none'
    b.style.display = 'none'
    c.style.display = 'block'
    */
}