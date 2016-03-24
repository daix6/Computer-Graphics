;((doc, t3, undefined) => {

'use strict';

class App {
  constructor() {
    this.scene = new t3.Scene;
    this.renderer = new t3.WebGLRenderer;
    this.renderer.setSize(window.innerWidth, window.innerHeight);
    doc.body.appendChild(this.renderer.domElement);
  }

  setCamera() {
    this.camera = new t3.PerspectiveCamera(75, window.innerWidth/window.innerHeight, 0.1, 1000);
    this.position.z = 5;
  }

  addCube() {
    let geometry = new t3.BoxGeometry(1, 1, 1);
    let material = new t3.MeshBasicMaterial({color: 0x00ff00});
    this.cube = new t3.Mesh(geometry, material);
    this.scene.add(cube);
  }

  render() {
    requestAnimationFrame(this.render);
    this.cube.rotation.x += 0.01;
    this.cube.rotation.y += 0.01;
    this.renderer.render(this.scene, this.camera);
  }
}

let a = new App;
a.setCamera();
a.addCube();
a.render();

})(document, THREE, undefined);