import React from 'react';
import { AppRegistry, NativeAppEventEmitter, NativeModules, StyleSheet, Text, View } from 'react-native';

const DemoModule = NativeModules.DemoModule;
var subscription = null;

export default class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = { label: "" };
  }

  componentWillMount() {
    subscription = NativeAppEventEmitter.addListener(DemoModule.EVENT_NAME, (e) => {
      this.appendLine("eventReceived: " + JSON.stringify(e));
    });

    this.test();
  }

  componentWillUnmount() {
    subscription.remove();
  }

  test() {
    this.promiseTest();
    this.callbackTest();
    this.eventTest();
  }

  async promiseTest() {
    this.appendLine("testPromise: " + await DemoModule.testPromise());
    this.appendLine("testMap: " + JSON.stringify(await DemoModule.testMap({a: DemoModule.INT_CONSTANT, b: 2})));
    this.appendLine("testBool: " + await DemoModule.testBool(DemoModule.BOOL_CONSTANT));
    this.appendLine("testString: " + await DemoModule.testString(DemoModule.STRING_CONSTANT));
  }

  callbackTest() {
    DemoModule.testArray([1, 2, 3, 4, null], (array) => this.appendLine("testArray: " + JSON.stringify(array)))
    DemoModule.testCallback((str) => this.appendLine("testCallback: " + str));
    DemoModule.testPrimitives(1, DemoModule.DOUBLE_CONSTANT, (i, d) => this.appendLine("testPrimitives: " + i + ", " + d));
  }

  eventTest() {
    DemoModule.testEventWithArray([1, "str", null]);
    DemoModule.testEventWithMap({a: 3, b: 8, c: "str"});
  }

  appendLine(str) {
    this.updateLabel(this.state.label + str + "\n")
  }

  updateLabel(str) {
    this.setState({ label: str });
  }

  render() {
    return (
      <View style={styles.container}>
        <Text>{this.state.label}</Text>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});

AppRegistry.registerComponent('rncpp', () => App);
