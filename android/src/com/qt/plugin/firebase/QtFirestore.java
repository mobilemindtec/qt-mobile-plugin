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

public class QtFirestore{

    private static String TAG = "QtFirestore";
    private static FirebaseFirestore db;

    private static native void static_firestoreReadResult(String collection, String[] results);
    private static native void static_firestoreReadResult2(String collection, List<Map<String, Object>> results);
    private static native void static_firestoreError(String error);

    public void init() {
        if(this.db == null){
            try{
                Log.i(TAG, "Firebase init..");
                this.db = FirebaseFirestore.getInstance();
                Log.i(TAG, "Firebase OK!");
            }catch(Exception e){
                static_firestoreError("Firebase init error: " + e.getMessage());
                Log.w(TAG, "Firebase init error:", e);
            }
        }

    }

    public void firestoreRead(String collection){

        this.init();
        Log.i(TAG, "firestireRead java called from c++");

        db.collection(collection)
            .get()
            .addOnCompleteListener(new OnCompleteListener<QuerySnapshot>() {
                @Override
                public void onComplete(@NonNull Task<QuerySnapshot> task) {
                    Log.i(TAG, "onComplete");
                    if (task.isSuccessful()) {

                        List<String> results = new LinkedList<String>();
                        List<Map<String,Object>> results2 = new LinkedList<Map<String, Object>>();

                        for (QueryDocumentSnapshot document : task.getResult()) {
                            Log.d(TAG, document.getId() + " => " + document.getData());
                            results.add(document.getData().toString());
                            results2.add(document.getData());
                        }

                        Log.i(TAG, "call c++ from java");
                        static_firestoreReadResult(collection, results.toArray(new String[results.size()]));

                        static_firestoreReadResult2(collection, results2);

                    } else {
                        static_firestoreError("Error getting documents:" + task.getException());
                        Log.w(TAG, "Error getting documents.", task.getException());
                    }
                }
            });
        Log.i(TAG, "firestireRead java called from c++.. done");
    }
}
