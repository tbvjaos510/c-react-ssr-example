import React from 'react';

export default class App extends React.Component {
  componentDidMount() {
    console.log("mounted!");
  }
  render() {
    return (
      <div>Hello World!</div>
    )
  }
}