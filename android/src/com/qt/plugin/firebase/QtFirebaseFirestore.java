package com.qt.plugin.firebase;

import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.WorkerThread;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.android.gms.tasks.Tasks;
import com.google.firebase.Timestamp;
import com.google.firebase.firestore.CollectionReference;
import com.google.firebase.firestore.DocumentChange;
import com.google.firebase.firestore.DocumentChange.Type;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.DocumentSnapshot;
import com.google.firebase.firestore.EventListener;
import com.google.firebase.firestore.FieldPath;
import com.google.firebase.firestore.FieldValue;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.FirebaseFirestoreException;
import com.google.firebase.firestore.FirebaseFirestoreSettings;
import com.google.firebase.firestore.ListenerRegistration;
import com.google.firebase.firestore.MetadataChanges;
import com.google.firebase.firestore.Query;
import com.google.firebase.firestore.Query.Direction;
import com.google.firebase.firestore.QueryDocumentSnapshot;
import com.google.firebase.firestore.QuerySnapshot;
import com.google.firebase.firestore.ServerTimestamp;
import com.google.firebase.firestore.SetOptions;
import com.google.firebase.firestore.Source;
import com.google.firebase.firestore.Transaction;
import com.google.firebase.firestore.WriteBatch;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.Executor;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import com.qt.plugin.core.QtChannel
import com.qt.plugin.core.QtChannelMessage

public class QtFirebaseFirestore{

    private final String ChannelName = "firebase.Firestore"
    private final String MethodInit = "init";
    private final String MethodRead = "read";

    private static String TAG = "QtFirebaseFirestore";
    private static FirebaseFirestore db;
    private QtChannelMessage currentMessage;
    private boolean initOk;

    //private static native void static_firestoreReadResult(String collection, String[] results);
    //private static native void static_firestoreReadResult2(String collection, List<Map<String, Object>> results);
    //private static native void static_firestoreError(String error);

    public void getChannelName() {
        return ChannelName;
    }

    public void register(){
        channelRegister(ChannelName, this);
    }

    public void callMethod(QtChannelMessage message){

        this.currentMessage = message;

        switch(message.getMethodName()){
            case MethodInit:
                init();
            break;
            case MethodRead:

                String collectionName = message.firstArg();

                this.read(collectionName);
            break;
            default:
                sendError("method not available", this.currentMessage);
        }
    }

    public void init() {
        if(this.db == null){
            try{
                Log.i(TAG, "Firebase init..");
                this.db = FirebaseFirestore.getInstance();
                Log.i(TAG, "Firebase OK!");
                this.initOk = true;
            }catch(Exception e){                
                Log.w(TAG, "Firebase init error:", e);
                sendError(e, "error on init firestore: " + e.getMessage(), this.currentMessage);
            }
        }

    }

    public void read(String collection){

        Log.i(TAG, "read");

        if(!this.initOk){
            sendError("firebase not initialized", this.currentMessage);
            return
        }


        db.collection(collection)
            .get()
            .addOnCompleteListener(new OnCompleteListener<QuerySnapshot>() {
                @Override
                public void onComplete(@NonNull Task<QuerySnapshot> task) {
                    Log.i(TAG, "onComplete");
                    if (task.isSuccessful()) {

                        List<Map<String,Object>> results = new LinkedList<Map<String, Object>>();

                        for (QueryDocumentSnapshot document : task.getResult()) {
                            results.add(document.getData());
                        }

                        Log.i(TAG, "call c++ from java");
                        sendData(currentMessage, results);

                    } else {                        
                        Log.w(TAG, "Error getting documents.", task.getException());
                        sendError(task.getException(), "firebase task error: " + task.getException().getMessage(), this.currentMessage);
                    }
                }
            });
        Log.i(TAG, "firestireRead java called from c++.. done");
    }
}
