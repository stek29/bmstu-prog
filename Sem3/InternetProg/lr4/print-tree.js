'use strict';

window.printTreeInit = function (el) {
    const classPrefix = 'print-tree-';
    const indentWith = '&nbsp;';
    const maxDepth = 100;
    
    var context = {};
    context.element = el;

    context.resultElement = document.createElement('pre');
    context.resultElement.className = classPrefix + 'result';

    context.printButton = document.createElement('button');
    context.printButton.innerHTML = 'Вывести';

    context.print = (function (text) {
        console.debug('print: ', text);
        this.resultElement.innerHTML += text;
    }).bind(context);
    
    context.clear = (function () {
        this.resultElement.innerHTML = '';
    }).bind(context);

    context.traverseDOM = (function (element, depth) {
        console.log('traverseDOM(', element, depth, ')');
        depth = depth || 0;
        if (depth >= maxDepth) {
            console.warn('maxdepth reached!');
            return;
        }
        
        if ((!element)
            || (element.className||'').startsWith(classPrefix)
            || (element.nodeName == '#text')
           ) return;
        
        
        this.print([
            indentWith.repeat(depth),
            '&lt;', element.tagName, '&gt;',
            '\n'
        ].join(''));
        
        element.childNodes.forEach(e => this.traverseDOM(e, depth+1));
    }).bind(context);
    
    var printFunction = (function () {
        this.clear();
        this.printButton.disabled = true;
        this.traverseDOM(this.element);
        this.printButton.disabled = false;
    }).bind(context);

    context.printButton.onclick = printFunction;

    context.wrapper = document.createElement('div');
    context.wrapper.className = classPrefix + 'wrapper';
    
    context.wrapper.appendChild(context.resultElement);
    context.wrapper.appendChild(document.createElement('br'));
    context.wrapper.appendChild(context.printButton);
    
    context.element.appendChild(context.wrapper);
};